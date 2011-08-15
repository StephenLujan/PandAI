////////////////////////////////////////////////////////////////////////
// Filename    : seek.cxx
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

#include "seek.h"

Seek::Seek(AICharacter *ai_ch, NodePath target_object, float max_weight, bool arrival)
: SteeringObjective(ai_ch, max_weight) {

  _seek_position = target_object.get_pos(_ai_char->_window_render);
  _seek_done = false;
  _arrival = arrival;
}

Seek::Seek(AICharacter *ai_ch, LVecBase3f pos, float max_weight, bool arrival)
: SteeringObjective(ai_ch, max_weight) {

  _seek_position = pos;
  _seek_done = false;
  _arrival = arrival;
}

Seek::~Seek() {
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : get_desired_velocity
// Description :  This function performs the seek and returns a seek velocity which
//                which is used in the get_desired_force() function, or an 
//                ObjectiveList's get_desired_velocity function.
//
/////////////////////////////////////////////////////////////////////////////////

LVecBase3f Seek::get_desired_velocity() {

  LVecBase3f to_target = _seek_position - _ai_char->_ai_char_np.get_pos(_ai_char->_window_render);
  double target_distance = to_target.length();

  if(int(target_distance) == 0) {
    _seek_done = true;
    _weight = 0;
    return(LVecBase3f(0.0, 0.0, 0.0));
  }
  _weight = _max_weight;
  to_target.normalize();

  double speed = _ai_char->_max_speed;
  if (_arrival) {
    double stoppingSpeed = get_max_stopping_speed(target_distance);
    if (stoppingSpeed < speed)
      speed = stoppingSpeed;
  }

  LVecBase3f desired_velocity = to_target * speed;
  return(desired_velocity);
}