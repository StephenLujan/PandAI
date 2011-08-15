////////////////////////////////////////////////////////////////////////
// Filename    : flee.h
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

#ifndef _FLEE_H
#define _FLEE_H

#include "aiGlobals.h"
#include "aiCharacter.h"
#include "steeringObjective.h"

class AICharacter;

class EXPCL_PANDAAI Flee : public SteeringObjective {

public:

  LVecBase3f _flee_position;
  LVecBase3f _flee_direction;
  double _panic_distance;
  double _relax_distance;
  LVecBase3f _flee_present_pos;

  Flee(AICharacter *ai_ch, NodePath target_object, double panic_distance = 10.0,
                              double relax_distance = 10.0, float max_weight = 1.0);

  Flee(AICharacter *ai_ch, LVecBase3f pos, double panic_distance = 10.0,
                              double relax_distance = 10.0, float max_weight = 1.0);

  ~Flee();
  void activation_check();
  LVecBase3f get_desired_velocity();
};

#endif
