////////////////////////////////////////////////////////////////////////
// Filename    : Intercept.cxx
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

#include "intercept.h"
#include <math.h>

/*

In order to project the best interception point between a moving
objective and a pursuer some assumptions must be made. For our purposes 
we will assume the velocity of the target is constant.

Imagine a triangle who's corners are P T and I for pursuer, target,
and the future interception point respectively. The angles enclosed 
are p t and i. 

P
|\
|p\
|  \
|   \PI
|PT  \
|     \
|      \
|t_____i\
T   TI   I


Because the location of I is unknown the only known
angle is t, the angle between the target's current velocity and the
pursuer. Side PT is known as it is the present distance between 
target and pursuer. We know that the pursuer's and target's
respective distances to their intercept point is proportionate
to their speeds. Using their speeds we can find the ratio between
PT and TI.

knowns: PT, t, (PT : TI)
unknowns: PI, TI, p, i, 

sin t / PT = sin p / TI

Using the law of sines. We can simply replace the unknown sides
with their velocity. Having the same ratio as the actual lengths,
the equation is still balanced and true.

sin t / Pv = sin p / Tv
Tv sin t = Pv sin p
sin p = (Tv sin t)/Pv
p = arcsin((Tv sin t)/Pv)


Now p is expressed in known quantities and can be calculated. Now 
we can find the remaining angle because all angles in a triangle 
add up to 180 degrees or pi radians. 

Now there are many ways to find I, but I would like to just scale 
target velocity to the length of side TI. Because we know PT we 
can find the length of side TI using the law of sines again.

sin p / TI =  sin i / PT
TI sin i = PT sin p
TI = (PT sin p) / sin i

Putting it together all that's left for the computer to do is:
p = arcsin((Tv sin t)/Pv)
i = PI - p - t
TI = (PT sin p) / sin i

*/


double target_to_intercept( double distance_to_target, double target_angle, double target_speed, double pursuer_speed)
{
	double pursuer_angle = asin((target_speed * sin(target_angle) / pursuer_speed));
	double intercept_angle = 3.14159265 - pursuer_angle - target_angle;
	double target_to_intercept = distance_to_target * sin(pursuer_angle) / sin(intercept_angle);
  return target_to_intercept;
}

LVecBase3f find_intercept( LVecBase3f target_pos, LVecBase3f pursuer_pos, LVecBase3f target_velocity, double pursuer_speed)
{
	
	LVecBase3f target_to_pursuer = pursuer_pos - target_pos;
	double distance_to_target = target_to_pursuer.length();
  double target_speed = target_velocity.length();
  double target_angle = acos (target_to_pursuer.dot(target_velocity) / (distance_to_target * target_speed));
	double intercept_distance = target_to_intercept( distance_to_target, target_angle, target_speed, pursuer_speed);

  target_velocity.normalize();
	LVecBase3f intercept_point = target_pos + target_velocity * intercept_distance;
	return intercept_point;
}
