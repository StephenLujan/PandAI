////////////////////////////////////////////////////////////////////////
// Filename    : evade.cxx
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

#include "evade.h"

Evade::Evade(AICharacter *ai_ch, NodePath target_object, double panic_distance,
                                          double relax_distance, float max_weight)
: SteeringObjective(ai_ch, max_weight) {


  _evade_target = target_object;
  _panic_distance = panic_distance;
  _relax_distance = relax_distance;
}

Evade::~Evade() {
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : activation_check
// Description : This function performs the evade and returns an evade force which is used
//                in the calculate_prioritized function.
//                In case the AICharacter is past the (panic + relax) distance,
//                it resets to evade_activate.
//                This function is not to be used by the user.

/////////////////////////////////////////////////////////////////////////////////

LVecBase3f Evade::get_desired_velocity() {
  assert(_evade_target && "evade target not assigned");

  _evade_direction = _ai_char->_ai_char_np.get_pos(_ai_char->_window_render) - _evade_target.get_pos(_ai_char->_window_render);
  double distance = _evade_direction.length();

  if(distance > _panic_distance + _relax_distance) {
    _active = false;
    return(LVecBase3f(0.0, 0.0, 0.0));
  }

  _evade_direction.normalize();
  _weight = distance / (_panic_distance + _relax_distance) * _max_weight;
  LVecBase3f desired_velocity = _evade_direction * _ai_char->_max_speed;

  return(desired_velocity);

}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : activation_check
// Description : This function checks for whether the target is within the panic distance.
//                When this is true, it calls the do_evade function and sets the evade direction.
//                This function is not to be used by the user.

/////////////////////////////////////////////////////////////////////////////////

void Evade::activation_check() {
    _evade_direction = (_ai_char->_ai_char_np.get_pos(_ai_char->_window_render) - _evade_target.get_pos(_ai_char->_window_render));
  double distance = _evade_direction.length();
  //_evade_activate_done = false;

  if(distance < _panic_distance) {
    _active = true;
  }
}
