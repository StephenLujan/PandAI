////////////////////////////////////////////////////////////////////////
// Filename    : steeringObjective.cxx
// Created by  : Stephen Lujan
// Date        : 14 Aug 11
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

#include "steeringObjective.h"

SteeringObjective::SteeringObjective(AICharacter *ai_ch, float max_weight){
  _ai_char = ai_ch;
  _max_weight = max_weight;
  _weight = max_weight;
  _on = true;
}

SteeringObjective::~SteeringObjective(){
}

float SteeringObjective::get_weight(){
  return _weight;
}

void SteeringObjective::set_max_weight(float max_weight){
  _max_weight = max_weight;
}

bool SteeringObjective::is_on(){
  return _on;
}

bool SteeringObjective::is_off(){
  return !_on;
}

void SteeringObjective::turn_off(){
  _on = false;
}

void SteeringObjective::turn_on(){
  _on = true;
}

bool SteeringObjective::is_active() {
  return _active;
}

bool SteeringObjective::operator==(const SteeringObjective &other) const {
  return (this == &other);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : get_max_stopping_speed
// Description :  This function returns the greatest speed which will still allow 
//                the ai to stop in the input distance. This is useful for 
//                arrival behaviors. 
//
/////////////////////////////////////////////////////////////////////////////////

string SteeringObjective::behavior_status(){
  if(this->is_on())
    if (this->is_active())
      return "active";
    else
      return "sleeping";
  else
    return "paused";
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : activation_check
// Description :  This function will wake a non-active SteeringObjective should
//                it meet the right conditions. e.g. Flee below panic distance
//
/////////////////////////////////////////////////////////////////////////////////
    
void SteeringObjective::activation_check() {
  _active = true;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : get_max_stopping_speed
// Description :  This function returns the greatest speed which will still allow 
//                the ai to stop in the input distance. This is useful for 
//                arrival behaviors. 
//
/////////////////////////////////////////////////////////////////////////////////

double SteeringObjective::get_max_stopping_speed(double distance){
    // Once again, here's the physics for dummies:
    // delta Position = Velocity * Time
    // stopping distance = (average speed) * (time to decelerate to 0)
    // stopping distance = (0.5 * current speed) * (current speed / acceleration)
    // d = 0.5 * s * s / a
    // 2da = s^2
    // s = sqrt(2da)
    return sqrt(2 * distance * _ai_char->_max_acceleration);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : get_desired_velocity
// Description :  This function returns the desired velocity of a steering
//                objective. Most behaviors will have their own way of getting
//                a desired velocity, from which a desired force can always be 
//                derived in the same way.
//
/////////////////////////////////////////////////////////////////////////////////

LVecBase3f SteeringObjective::get_desired_velocity(){
  return LVecBase3f(0.0, 0.0, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : get_desired_velocity
// Description :  This function returns the desired force of a steering 
//                objective. Most steering behaviors will want a specific
//                velocity and the force is just needed for physics calculations.
//
/////////////////////////////////////////////////////////////////////////////////

LVecBase3f SteeringObjective::get_desired_force(){

  // We want our steering force to alter the current velocity into the desired velocity.
  // The desired direction of the force can thus be obtained with simple subtraction.
  LVecBase3f force = this->get_desired_velocity() - _ai_char->get_velocity();

  // Now that we have the direction we convert the amount to the ai's max force.
  // The only reason we wouldn't want to use max force is if it would cause us
  // to overshoot our desired velocity. There are some rudimentary physics to consider.
  float speed_difference_desired = force.length();
  force.normalize();
  force *= _ai_char->get_max_force();
  // force / mass = acceleration
  // acceleration * time = delta velocity
  float speed_difference_projected = force.length() / _ai_char->get_mass() * _ai_char->_delta_t;
  if (speed_difference_projected > speed_difference_desired)
    force *= speed_difference_desired / speed_difference_projected;
  
  return force;
}

