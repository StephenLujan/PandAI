////////////////////////////////////////////////////////////////////////
// Filename    : objectiveList.h
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

////////////////////////////////////////////////////////////////////
// SELECTIVE  steering uses the objective with the highest weight
//            and discards the rest.
//
// CUMULATIVE steering uses a weighted average of all of its
//            member objectives.
////////////////////////////////////////////////////////////////////
// THOROUGH   steering will calculate the desired force for each
//            of its combined objectives.
//
// FAST       steering will only calculate the desired velocity for
//            each of its combined objectives, and yield a single 
//            desired force.
////////////////////////////////////////////////////////////////////
// MAXSPEED   steering will manipulate mostly cumulative steering by
//            scaling desired velocity or force to their maximums.
//            This may be desireable if you are compositing similar
//            objectives like multiple flee targets.
//
// VARIABLE   steering maintains the weighted average from
//            cumulative steering unmodified. This may be desireable
//            if you are combining objectives that themselves do not
//            always want maximum speed like arrival or flocking.
////

#ifndef _OBJECTIVE_LIST_H
#define _OBJECTIVE_LIST_H

class AICharacter;
#include "aiGlobals.h"
#include "steeringObjective.h"

class EXPCL_PANDAAI ObjectiveList : public SteeringObjective {
  public:
    typedef SteeringObjective Parent;
    typedef list<SteeringObjective, allocator<SteeringObjective>> OList;
    OList objectives;
    OList::iterator itr;
    
    bool cumulative;
    bool get_all_forces;
    bool use_max_speed;
    bool activate;

    ObjectiveList(AICharacter *ai_ch, float max_weight = 1.0);
    ~ObjectiveList();

    void activation_check();
    void add_objective(SteeringObjective *obj);
    void remove_objective(SteeringObjective *obj);
    void remove_all();
    virtual LVecBase3f get_desired_velocity();
    virtual LVecBase3f get_desired_force();
};

#endif