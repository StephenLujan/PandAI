////////////////////////////////////////////////////////////////////////
// Filename    : flockObjective.cxx
// Created by  : Deepak, John, Navin, Stephen
// Date        :  17 Aug 11
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#include "flockObjective.h"
#include "aiCharacter.h"


FlockObjective::FlockObjective(AICharacter *ai_ch, float max_weight)
: SteeringObjective(ai_ch, max_weight) {
}

FlockObjective::~FlockObjective() {
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : get_desired_velocity
// Description : This function contains the logic for flocking behavior. This is
//                an emergent behavior and is obtained by combining three other
//                behaviors which are separation, cohesion and alignment based on
//                Craig Reynold's algorithm. Also, this behavior does not work by
//                itself. It works only when combined with other steering behaviors
//                such as wander, pursue, evade, seek and flee.

/////////////////////////////////////////////////////////////////////////////////

LVecBase3f FlockObjective::get_desired_velocity() {

  //! Initialize variables required to compute the flocking force on the ai char.
  unsigned int neighbor_count = 0;
  LVecBase3f separation_force = LVecBase3f(0.0, 0.0, 0.0);
  LVecBase3f alignment_force = LVecBase3f(0.0, 0.0, 0.0);
  LVecBase3f cohesion_force = LVecBase3f(0.0, 0.0, 0.0);
  LVecBase3f avg_neighbor_heading = LVecBase3f(0.0, 0.0, 0.0);
  LVecBase3f total_neighbor_heading = LVecBase3f(0.0, 0.0, 0.0);
  LVecBase3f avg_center_of_mass = LVecBase3f(0.0, 0.0, 0.0);
  LVecBase3f total_center_of_mass = LVecBase3f(0.0, 0.0, 0.0);
  LVecBase3f desired_velocity = LVecBase3f(0.0, 0.0, 0.0);

  //! Loop through all the other AI units in the flock to check if they are neigbours.
  for(unsigned int i = 0; i < _flock_group->_ai_char_list.size(); i++) {
    if(_flock_group->_ai_char_list[i]->_name != _ai_char->_name) {

      //! Using visibilty cone to detect neighbors.
      LVecBase3f dist_vect = _flock_group->_ai_char_list[i]->_ai_char_np.get_pos() - _ai_char->_ai_char_np.get_pos();
      LVecBase3f ai_char_heading = _ai_char->get_velocity();
      ai_char_heading.normalize();

      //! Check if the current unit is a neighbor.
      if(dist_vect.dot(ai_char_heading) > ((dist_vect.length()) * (ai_char_heading.length()) * cos(_flock_group->_flock_vcone_angle * (_PI / 180)))
        && (dist_vect.length() < _flock_group->_flock_vcone_radius)) {
          //! Separation force calculation.
          // scaled by inverse of distance... potentially infinite
          LVecBase3f ai_char_to_units = _ai_char->_ai_char_np.get_pos() - _flock_group->_ai_char_list[i]->_ai_char_np.get_pos();
          float to_units_dist = ai_char_to_units.length();
          ai_char_to_units.normalize();
          separation_force += (ai_char_to_units / to_units_dist);

          //! Calculating the total heading and center of mass of all the neighbors.
          LVecBase3f neighbor_heading = _flock_group->_ai_char_list[i]->get_velocity();
          //neighbor_heading.normalize();
          //total_neighbor_heading += neighbor_heading;
          total_center_of_mass += _flock_group->_ai_char_list[i]->_ai_char_np.get_pos();

          //! Update the neighbor count.
          ++neighbor_count;
      }
    }
  }

  if(neighbor_count > 0) {
    //! Alignment force calculation
    // components scaled by speed, ergo the whole thing is scaled by speed
    avg_neighbor_heading = total_neighbor_heading / neighbor_count;
    LVector3f ai_char_heading = _ai_char->get_velocity();
    //ai_char_heading.normalize();
    avg_neighbor_heading -= ai_char_heading;
   // avg_neighbor_heading.normalize();
    alignment_force = avg_neighbor_heading;

    //! Cohesion force calculation
    // scaled by speed
    avg_center_of_mass = total_center_of_mass / neighbor_count;
    LVecBase3f cohesion_dir = avg_center_of_mass - _ai_char->_ai_char_np.get_pos();
    cohesion_dir.normalize();
    cohesion_force = cohesion_dir * _ai_char->_max_speed;
  }
  // No neighbors? If we have other things to do just disable the flock objective.
  else if(! _ai_char->get_ai_behaviors()->objectives.empty()) {
    this->turn_off();
    //turn_on("flock_activate");
    return(LVecBase3f(0.0, 0.0, 0.0));
  }
  
  //! Calculate the resultant velocity on the ai character by taking into account the separation, alignment
  //! and cohesion forces along with their corresponding weights.
  desired_velocity = (separation_force * _flock_group->_separation_wt + alignment_force * _flock_group->_alignment_wt
    + cohesion_force * _flock_group->_cohesion_wt);

  return desired_velocity;
}


/////////////////////////////////////////////////////////////////////////////////
//
// Function : activation_check
// Description : This function checks whether any other behavior exists to work with flock.
//                When this is true, it calls the do_flock function.

/////////////////////////////////////////////////////////////////////////////////

void FlockObjective::activation_check() {

  AIBehaviors* behavior = _ai_char->get_ai_behaviors();
  if(behavior->_seek_obj->is_on() || behavior->_flee_obj->is_on() || behavior->_pursue_obj->is_on() || behavior->_evade_obj->is_on() || behavior->_wander_obj->is_on()) {
      behavior->_flock_obj->turn_on();
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : leave_flock
// Description : This function removes this ai from the flock but leaves the 
//               FlockObjective on the ai.
//
/////////////////////////////////////////////////////////////////////////////////

void FlockObjective::leave_flock() {
  for(unsigned int i = 0; i < _flock_group->_ai_char_list.size(); ++i) {
    if(_flock_group->_ai_char_list[i] == _ai_char)
      _flock_group->_ai_char_list.erase(_flock_group->_ai_char_list.begin()+i);
  }
  _active = false;
}