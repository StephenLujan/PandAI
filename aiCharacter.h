////////////////////////////////////////////////////////////////////////
// Filename    : aiCharacter.h
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

#pragma warning (disable:4996)
#pragma warning (disable:4005)
#pragma warning(disable:4275)


#ifndef _AICHARACTER_H
#define _AICHARACTER_H

#include "aiGlobals.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Class : AICharacter
//  Description : This class is used for creating the ai characters. It assigns both physics and ai
//                attributes to the character. It also has an update function which updates the physics and ai
//                of the character. This update function is called by the AIWorld update.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Linear Kinematics for Dummies who can't even do their own algebrah:
// 
// Velocity = delta Position / Time
// Velocity * Time = delta Position
//
// Acceleration = delta Velocity / Time
// Acceleration * Time =  delta Velocity
//
// Acceleration = Force / Mass
// Force = Mass * Acceleration

class AIBehaviors;
class AIWorld;

class EXPCL_PANDAAI AICharacter {
  public:
    double _mass;
    double _max_speed;
    LVecBase3f _velocity;
    LVecBase3f _steering_force;
    string _name;
    double _max_acceleration;
    double _max_force;
    double _delta_t;
    
    AIWorld *_world;
    AIBehaviors *_steering;
    NodePath _window_render;
    NodePath _ai_char_np;
    bool _pf_guide;

    void update();
    void set_velocity(LVecBase3f vel);
    void set_char_render(NodePath render);
    NodePath get_char_render();

  PUBLISHED:
    double get_mass();
    void set_mass(double m);

    LVecBase3f get_velocity();

    double get_max_speed();
    void set_max_speed(double max_speed);

	  double get_max_acceleration();
    void set_max_acceleration(double max_acceleration);

	  double get_max_force();
    void set_max_force(double max_force);

    NodePath get_node_path();
    void set_node_path(NodePath np);

    AIBehaviors * get_ai_behaviors();

    // This function is used to enable or disable the guides for path finding.
    void set_pf_guide(bool pf_guide);

    AICharacter(string model_name, NodePath model_np, double mass, double max_acceleration, double max_speed);
    ~AICharacter();
};

#endif
