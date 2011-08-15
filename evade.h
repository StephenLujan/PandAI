////////////////////////////////////////////////////////////////////////
// Filename    : evade.h
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

#ifndef _EVADE_H
#define _EVADE_H

#include "aiGlobals.h"
#include "aiCharacter.h"

class AICharacter;

class EXPCL_PANDAAI Evade : public SteeringObjective {

public:
  NodePath _evade_target;
  LVecBase3f _evade_direction;
  double _panic_distance;
  double _relax_distance;

  Evade(AICharacter *ai_ch, NodePath target_object, double panic_distance,
                                          double relax_distance, float max_weight);

  ~Evade();
  LVecBase3f get_desired_velocity();
  void activation_check();
};

#endif
