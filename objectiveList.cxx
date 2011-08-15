////////////////////////////////////////////////////////////////////////
// Filename    : objectiveList.cxx
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

#include "ObjectiveList.h"

ObjectiveList::ObjectiveList(AICharacter *ai_ch, float max_weight)
: SteeringObjective(ai_ch, max_weight) {
  cumulative = true;
  get_all_forces = false;
  use_max_speed = true;
  activate = false;
}

ObjectiveList::~ObjectiveList(){
  remove_all();
}

void ObjectiveList::add_objective(SteeringObjective *obj){
  objectives.insert(objectives.end(), *obj);
}

void ObjectiveList::remove_objective(SteeringObjective *obj){
  objectives.remove(*obj);
}

void ObjectiveList::remove_all() {
  while (! objectives.empty())
    objectives.pop_front();
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : activation_check
// Description :  This function will wake a non-active SteeringObjective should
//                it meet the right conditions. e.g. Flee below panic distance
//
/////////////////////////////////////////////////////////////////////////////////
    
void ObjectiveList::activation_check() {
  for(itr = objectives.begin(); itr != objectives.end(); itr++) {
    if (! itr->is_active())
      itr->activation_check();
  }
}

////////////////////////////////////////////////////////////////////

LVecBase3f ObjectiveList::get_desired_velocity(){

  LVecBase3f velocity = LVecBase3f(0.0, 0.0, 0.0); // desired velocity
  if (cumulative) {
    float totalWeight = 0;  // the sum of the weights of each priority being considered

    for(itr = objectives.begin(); itr != objectives.end(); itr++) {
      velocity += itr->get_desired_velocity() * itr->get_weight();
      totalWeight += itr->get_weight();
    }
    velocity /= totalWeight;

    _weight = totalWeight;
    if (_weight > _max_weight)
      _weight = _max_weight;
  }
  else {
    float highestWeight = 0.0;

    for(itr = objectives.begin(); itr != objectives.end(); itr++) {
      if (itr->get_weight() > highestWeight) {
        velocity = itr->get_desired_velocity() * itr->get_weight();
        highestWeight = itr->get_weight();
      }
    }

    _weight = highestWeight;
    if (_weight > _max_weight)
      _weight = _max_weight;
  }
  if (use_max_speed) {
    velocity.normalize();
    velocity *= _ai_char->get_max_speed();
  }
  return velocity;
}

LVecBase3f ObjectiveList::get_desired_force(){

  LVecBase3f force = LVecBase3f(0.0, 0.0, 0.0); // desired velocity
  if (! get_all_forces) {
    force = Parent::get_desired_force();
  }
  else {
    this->activation_check();
    if (cumulative) {
      float totalWeight = 0;  // the sum of the weights of each priority being considered

      for(itr = objectives.begin(); itr != objectives.end(); itr++) {
        force += itr->get_desired_force() * itr->get_weight();
        totalWeight += itr->get_weight();
      }
      force /= totalWeight;

      _weight = totalWeight;
      if (_weight > _max_weight)
        _weight = _max_weight;
    }
    else {
      float highestWeight = 0.0;

      for(itr = objectives.begin(); itr != objectives.end(); itr++) {
        if (itr->get_weight() > highestWeight) {
          force = itr->get_desired_force() * itr->get_weight();
          highestWeight = itr->get_weight();
        }
      }

      _weight = highestWeight;
      if (_weight > _max_weight)
        _weight = _max_weight;
    }
  }
  if (use_max_speed) {
    force.normalize();
    force *= _ai_char->get_max_force();
  }
  return force;
}
