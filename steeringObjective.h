////////////////////////////////////////////////////////////////////////
// Filename    : steeringObjective.h
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

#ifndef _STEERING_OBJECTIVE_H
#define _STEERING_OBJECTIVE_H

#include "aiGlobals.h"

class AICharacter;

class EXPCL_PANDAAI SteeringObjective {
  public:
    //The ai character that possesses this objective
    AICharacter *_ai_char;
    //The greatest weight this objective can hold against others
    float _max_weight;
    //The current weight of this objective
    float _weight;
    //Allows a steering objective to be paused
    bool _on;
    //Allows a steering objective to sleep/wake on its own
    bool _active;

    SteeringObjective(AICharacter *ai_ch, float max_weight = 1.0);
    ~SteeringObjective();

    float get_weight();
    void set_max_weight(float weight);
    bool is_on();
    bool is_off();
    void turn_off();
    void turn_on();
    bool is_active();
    virtual void activation_check();
    virtual string behavior_status();
    bool operator==(const SteeringObjective &other) const;

    double get_max_stopping_speed(double distance);
    // Most steering behaviors will yield a desired velocity, from
    // which a desired force can be derived in the same manner.
    virtual LVecBase3f get_desired_velocity();
    virtual LVecBase3f get_desired_force();
};

#endif