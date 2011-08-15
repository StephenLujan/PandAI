////////////////////////////////////////////////////////////////////////
// Filename    :  aiCharacter.cxx
// Created by  :  Deepak, John, Navin, Stephen
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

#include "aiCharacter.h"

AICharacter::AICharacter(string model_name, NodePath model_np, double mass, double max_acceleration, double max_speed) {
  _name = model_name;
  _ai_char_np = model_np;

  _mass = mass;
  _max_speed = max_speed;
  _max_acceleration = max_acceleration;
  _max_force = max_acceleration * mass;
  _velocity = LVecBase3f(0.0, 0.0, 0.0);
  _steering_force = LVecBase3f(0.0, 0.0, 0.0);
  _delta_t = 0;

  _steering = new AIBehaviors(this);

  _pf_guide = false;
}

AICharacter::~AICharacter() {
}

/////////////////////////////////////////////////////////////////////////////////////////
//
// Function : update
// Description : Each character's update will update its ai and physics
//                based on his resultant steering force.
//                This also makes the character look at the direction of the force.

/////////////////////////////////////////////////////////////////////////////////////////

void AICharacter::update() {


  LVecBase3f old_pos = _ai_char_np.get_pos();
	
	//previous physics didn't make sense and were frame rate dependent...
	double time = 0.1; //ok still frame rate dependent so far

  LVecBase3f acceleration = _steering->calculate_steering_force() * time;

	_velocity += acceleration;
	if (_velocity.length() > _max_speed)
	  _velocity *= _max_speed / _velocity.length();
  
  LVecBase3f pos = old_pos + _velocity * time;
  _ai_char_np.set_pos(pos);


  if(_velocity.length() > _max_speed / 20) {
	  LVecBase3f facing = pos + _velocity; // face forward motion
    _ai_char_np.look_at(facing);
  }

}

LVecBase3f AICharacter::get_velocity() {
  return _velocity;
}

void AICharacter::set_velocity(LVecBase3f velocity) {
  _velocity = velocity;
}

double AICharacter::get_mass() {
  return _mass;
}

void AICharacter::set_mass(double m) {
  _mass = m;
}

double AICharacter::get_max_speed() {
  return _max_speed;
}

void AICharacter::set_max_speed(double max_speed) {
  _max_speed = max_speed;
}

double AICharacter::get_max_force(){
  return _max_force;
}

void AICharacter::set_max_force(double max_force){
	_max_force = max_force;
}

double AICharacter::get_max_acceleration(){
  return _max_acceleration;
}

void AICharacter::set_max_acceleration(double max_acceleration){
	_max_acceleration = max_acceleration;
}

NodePath AICharacter::get_node_path() {
  return _ai_char_np;
}

void AICharacter::set_node_path(NodePath np) {
  _ai_char_np = np;
}

AIBehaviors * AICharacter::get_ai_behaviors() {
  return _steering;
}

void AICharacter::set_char_render(NodePath render) {
  _window_render = render;
}

NodePath AICharacter::get_char_render() {
  return _window_render;
}

void AICharacter::set_pf_guide(bool pf_guide) {
  _pf_guide = pf_guide;
}
