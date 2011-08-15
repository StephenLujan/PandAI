////////////////////////////////////////////////////////////////////////
// Filename    : wander.h
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

#ifndef _WANDER_H
#define _WANDER_H

#include "aiCharacter.h"

class AICharacter;

class EXPCL_PANDAAI Wander : public SteeringObjective {
  public:
    double _wander_radius;
    LVecBase3f _wander_target;
    int _flag;
    LVecBase3f _init_pos;
    double _area_of_effect;

    Wander(AICharacter *ai_ch, double wander_radius, int flag, double aoe, float max_weight = 1.0);
    LVecBase3f do_wander();
    ~Wander();
};

#endif
