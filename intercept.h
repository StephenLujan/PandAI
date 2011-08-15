////////////////////////////////////////////////////////////////////////
// Filename    : Intercept.h
// Created by  : Stephen Lujan
// Date        : March 9th 2011
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

#ifndef _INTERCEPT_H
#define _INTERCEPT_H

#include "aiGlobals.h"

double target_to_intercept( double distance_to_target, double target_angle, double target_speed, double pursuer_speed);

LVecBase3f find_intercept( LVecBase3f target_pos, LVecBase3f pursuer_pos, LVecBase3f target_velocity, double pursuer_speed);

#endif