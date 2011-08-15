////////////////////////////////////////////////////////////////////////
// Filename    : seek.h
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

#ifndef _SEEK_H
#define _SEEK_H

#include "aiGlobals.h"
#include "aiCharacter.h"
#include "steeringObjective.h"

class AICharacter;

class EXPCL_PANDAAI Seek : public SteeringObjective {
  public:
    typedef SteeringObjective Parent;
    bool _seek_done;
    bool _arrival; //Are we trying to stop at or match speed with our target
    LVecBase3f _seek_position;

    Seek(AICharacter *ai_ch, NodePath target_object, float max_weight = 1.0, bool arrival = true);
    Seek(AICharacter *ai_ch, LVecBase3f pos, float max_weight = 1.0, bool arrival = true);
    ~Seek();

    LVecBase3f get_desired_velocity();
    //get_desired_force is in SteeringObjective
};

#endif
