////////////////////////////////////////////////////////////////////////
// Filename    : pathFollow.h
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

#ifndef _PATHFOLLOW_H
#define _PATHFOLLOW_H

#include "aiGlobals.h"
#include "aiCharacter.h"
#include "meshNode.h"

class AICharacter;

class EXPCL_PANDAAI PathFollow : public SteeringObjective {

public:
  vector<LVecBase3f> _path;
  int _curr_path_waypoint;
  bool _start;
  NodePath _dummy;
  string _type;
  ClockObject *_myClock;
  float _time;

  PathFollow(AICharacter *ai_ch, float max_weight = 1.0);
  ~PathFollow();
  void add_to_path(LVecBase3f pos);
  void start(string type);
  void do_follow();
  bool check_if_possible();
};

#endif
