////////////////////////////////////////////////////////////////////////
// Filename    : aiBehaviors.cxx
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

#ifndef _AIBEHAVIORS_H
#define _AIBEHAVIORS_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Class : AIBehaviors
// Description : This class implements all the steering behaviors of the AI framework, such as
//                seek, flee, pursue, evade, wander and flock. Each steering behavior has a weight which is used when more than
//                one type of steering behavior is acting on the same ai character. The weight decides the contribution of each
//                type of steering behavior. The AICharacter class has a handle to an object of this class and this allows to
//                invoke the steering behaviors via the AICharacter. This class also provides functionality such as pausing, resuming
//                and removing the AI behaviors of an AI character at anytime.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AICharacter;
#include "aiGlobals.h"
#include "steeringObjective.h"
#include "objectiveList.h"
#include "Seek.h"
#include "Flee.h"
#include "Pursue.h"
#include "Evade.h"
#include "Flock.h"
#include "Wander.h"
#include "PathFollow.h"
#include "PathFind.h"
#include "ObstacleAvoidance.h"
#include "FlockObjective.h"


class EXPCL_PANDAAI AIBehaviors : public ObjectiveList {

public:
  enum _behavior_type {
      _none = 0x00000,
      _seek = 0x00002,
      _flee = 0x00004,
      _wander = 0x00008,
      _pursue = 0x00040,
      _evade = 0x00080,
      _flock = 0x00200,
      _obstacle_avoidance = 0x02000,
  };

  AICharacter* _ai_char;

  int _behaviors_flags;

  LVecBase3f _steering_force;

  SteeringObjective* _seek_obj;

  SteeringObjective* _flee_obj;

  SteeringObjective* _pursue_obj;

  SteeringObjective* _evade_obj;

  SteeringObjective* _wander_obj;

  SteeringObjective* _obstacle_avoidance_obj;

  PathFollow *_path_follow_obj;

  PathFind *_path_find_obj;

  FlockObjective* _flock_obj;

  AIBehaviors(AICharacter *ai_ch, float max_weight = 1.0);
  ~AIBehaviors();

  void add_to_type(SteeringObjective*& type, SteeringObjective* obj);
  void remove_ai(SteeringObjective* obj);
  int char_to_int(string ai_type);
  bool is_on(SteeringObjective* obj);

  LVecBase3f calculate_steering_force();

PUBLISHED:
  void seek(NodePath target_object, float seek_wt = 1.0);
  void seek(LVecBase3f pos, float seek_wt = 1.0);

  void flee(NodePath target_object, double panic_distance = 10.0, double relax_distance = 10.0, float flee_wt = 1.0);
  void flee(LVecBase3f pos, double panic_distance = 10.0, double relax_distance = 10.0, float flee_wt = 1.0);

  void pursue(NodePath target_object, float pursue_wt = 1.0);

  void evade(NodePath target_object, double panic_distance = 10.0, double relax_distance = 10.0, float evade_wt = 1.0);

  void flock(float flock_wt);

  void wander(double wander_radius = 5.0, int flag =0, double aoe = 0.0, float wander_weight = 1.0);

  void obstacle_avoidance(float feeler_length = 1.0);

  void path_follow(float follow_wt);
  void add_to_path(LVecBase3f pos);
  void start_follow(string type = "normal");

  // should have different function names.
  void init_path_find(const char* navmesh_filename);
  void path_find_to(LVecBase3f pos, string type = "normal");
  void path_find_to(NodePath target, string type = "normal");
  void add_static_obstacle(NodePath obstacle);
  void add_dynamic_obstacle(NodePath obstacle);

  void remove_ai(string ai_type);
  void pause_ai(string ai_type);
  bool is_on(string ai_type);
  void resume_ai(string ai_type);

  string behavior_status(string ai_type);
  string behavior_status();
};

#endif











