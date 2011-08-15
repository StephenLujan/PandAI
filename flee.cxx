////////////////////////////////////////////////////////////////////////
// Filename    : flee.cxx
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

#include "flee.h"

Flee::Flee(AICharacter *ai_ch, NodePath target_object, double panic_distance,
                                      double relax_distance, float max_weight)
: SteeringObjective(ai_ch, max_weight) {

  _flee_position = target_object.get_pos(_ai_char->_window_render);
  _panic_distance = panic_distance;
  _relax_distance = relax_distance;
}

Flee::Flee(AICharacter *ai_ch, LVecBase3f pos, double panic_distance,
                                double relax_distance, float _max_weight)
: SteeringObjective(ai_ch, _max_weight) {
  _flee_position = pos;
  _panic_distance = panic_distance;
  _relax_distance = relax_distance;
}

Flee::~Flee() {
}


/////////////////////////////////////////////////////////////////////////////////
//
// Function : activation_check
// Description :  This function will wake a Flee below panic distance
//
/////////////////////////////////////////////////////////////////////////////////
    
void Flee::activation_check() {
  LVecBase3f to_target = _flee_position - _ai_char->_ai_char_np.get_pos(_ai_char->_window_render);
  if (to_target.length() < (_panic_distance + _relax_distance))
    _active = true;
}


/////////////////////////////////////////////////////////////////////////////////
//
// Function : get_desired_velocity
// Description :  This function performs the flee and returns a flee velocity which
//                which is used in the get_desired_force() function, or an 
//                ObjectiveList's get_desired_velocity function. It will also
//                adjust weight with a linear drop-off toward its relax distance.
//
/////////////////////////////////////////////////////////////////////////////////

LVecBase3f Flee::get_desired_velocity() {

  LVecBase3f to_target = _flee_position - _ai_char->_ai_char_np.get_pos(_ai_char->_window_render);
  double distance = to_target.length();

  if(distance > (_panic_distance + _relax_distance)) {
    _weight = 0.0;
    _active = false;
    return to_target; //returned value doesn't matter if weight is 0;
  }
  else {
    _weight = _max_weight * distance / (_panic_distance + _relax_distance);
    to_target.normalize();
    LVecBase3f desired_velocity = to_target * -_ai_char->_max_speed;
    return desired_velocity;
  }
}