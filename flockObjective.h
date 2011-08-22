////////////////////////////////////////////////////////////////////////
// Filename    : flockObjective.h
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

#ifndef _FLOCK_OBJECTIVE_H
#define _FLOCK_OBJECTIVE_H

#include "aiGlobals.h"
#include "flock.h"
#include "steeringObjective.h"

class AICharacter;


///////////////////////////////////////////////////////////////////////////////////////
//
// Class : FlockObjective
// Description : This class is the individual ai's objective. It serves as somewhat of
//               a dummy to keep the steering interface consistent, but it can be
//               expanded to alter an individual's response to the flock.
//
///////////////////////////////////////////////////////////////////////////////////////

class EXPCL_PANDAAI FlockObjective : public SteeringObjective {
public:
  Flock* _flock_group;
  unsigned int _flock_id;

  FlockObjective(AICharacter *ai_ch, float max_weight = 1.0);
  ~FlockObjective();

  void activation_check();
  LVecBase3f get_desired_velocity();
  void leave_flock();
};

#endif