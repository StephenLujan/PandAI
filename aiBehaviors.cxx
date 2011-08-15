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


#include "aiBehaviors.h"

AIBehaviors::AIBehaviors(AICharacter *ai_ch, float max_weight)
: ObjectiveList(ai_ch, max_weight) {
  _steering_force = LVecBase3f(0.0, 0.0, 0.0);
  _behaviors_flags = _none;

  _seek_obj = NULL;
  _flee_obj = NULL;
  _pursue_obj = NULL;
  _evade_obj = NULL;
  _wander_obj = NULL;
  _flock_obj = NULL;
  _path_follow_obj = NULL;
  _path_find_obj = NULL;
  _obstacle_avoidance_obj = NULL;
}

AIBehaviors::~AIBehaviors() {

}

//////////////////////////////////////////////////////////////////////////////////////////////
//
// Function : add_to_type
// Description : 

//////////////////////////////////////////////////////////////////////////////////////////////
void AIBehaviors::add_to_type(SteeringObjective*& type, SteeringObjective* obj)
{
  if (type == NULL)
    type = obj;
  else {
    ObjectiveList* list = new ObjectiveList(obj->_ai_char, obj->_max_weight);
    list->add_objective(type);
    list->add_objective(obj);
    type = list;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////
//
// Function : calculate_steering_force
// Description : This function calculates the best steering force to help the AICharacter
//               reach its desired velocity and returns it to AICharacter's update.

//////////////////////////////////////////////////////////////////////////////////////////////

LVecBase3f AIBehaviors::calculate_steering_force() {
  return get_desired_force();
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : remove_ai
// Description : This function removes individual or all the AIs.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::remove_ai(SteeringObjective *obj) {
  if(obj != NULL) {
    objectives.remove(*obj);
    obj = NULL;
  }
}

//add for path follow
void AIBehaviors::remove_ai(string ai_type) {
  switch(char_to_int(ai_type)) {
    case 0: {
              remove_ai("seek");
              remove_ai("flee");
              remove_ai("pursue");
              remove_ai("evade");
              remove_ai("arrival");
              remove_ai("flock");
              remove_ai("wander");
              remove_ai("obstacle_avoidance");
              remove_ai("pathfollow");
              break;
            }

    case 1:  {
              remove_ai(_seek_obj);
              break;
            }

    case 2: {
              remove_ai(_flee_obj);
              break;
            }

    case 3: {
              remove_ai(_pursue_obj);
              break;
            }

    case 4: {
              remove_ai(_evade_obj);
              break;
            }

    case 6: {
              //remove_ai(_flock_obj);
              break;
            }

    case 7: {
              remove_ai(_wander_obj);
              break;
            }

    case 8: {
              remove_ai(_obstacle_avoidance_obj);
              break;
            }

    case 9: {
              remove_ai(_pursue_obj);
              break;
            }
    case 16:{
              remove_ai(_pursue_obj);
              remove_ai(_path_follow_obj);
              break;
            }
    default:
            cout<<"Invalid option!"<<endl;
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : pause_ai
// Description : This function pauses individual or all the AIs->

/////////////////////////////////////////////////////////////////////////////////

//add for path follow
void AIBehaviors::pause_ai(string ai_type) {
  switch(char_to_int(ai_type)) {
    case 0: {
              pause_ai("seek");
              pause_ai("flee");
              pause_ai("pursue");
              pause_ai("evade");
              pause_ai("arrival");
              pause_ai("flock");
              pause_ai("wander");
              pause_ai("obstacle_avoidance");
              pause_ai("pathfollow");
              break;
            }

    case 1:  {
              if(_seek_obj != NULL) {
                _seek_obj->turn_off();
              }
              break;
            }

    case 2: {
              if(_flee_obj != NULL){
                _flee_obj->turn_off();
              }
              break;
            }

    case 3: {
              if(_pursue_obj != NULL) {
                _pursue_obj->turn_off();
              }
              break;
            }

    case 4: {
              if(_evade_obj != NULL){
                _evade_obj->turn_off();
              }
              break;
            }

    case 6: {
              if(_flock_obj != NULL) {
                _flock_obj->turn_off();
              }
              break;
            }

    case 7: {
              if(_wander_obj != NULL) {
                _wander_obj->turn_off();
              }
              break;
            }

    case 8: {
              if(_obstacle_avoidance_obj != NULL) {
                _obstacle_avoidance_obj->turn_off();
              }
              break;
            }

    case 9: {
              if(_pursue_obj != NULL && _path_follow_obj != NULL) {
                _pursue_obj->turn_off();
                _path_follow_obj->turn_off();
              }
              break;
            }
    case 16: {
              if(_pursue_obj != NULL && _path_follow_obj != NULL) {
                _pursue_obj->turn_off();
                _path_follow_obj->turn_off();
              }
              break;
            }
    default:
            cout<<"Invalid option!"<<endl;
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : resume_ai
// Description : This function resumes individual or all the AIs

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::resume_ai(string ai_type) {
  switch(char_to_int(ai_type)) {
    case 0: {
              resume_ai("seek");
              resume_ai("flee");
              resume_ai("pursue");
              resume_ai("evade");
              resume_ai("arrival");
              resume_ai("flock");
              resume_ai("wander");
              resume_ai("obstacle_avoidance");
              resume_ai("pathfollow");
              break;
            }

    case 1:  {
              if(_seek_obj != NULL) {
                _seek_obj->turn_on();
              }
              break;
            }

    case 2: {
              if(_flee_obj != NULL){
                _flee_obj->turn_on();
              }
              break;
            }

    case 3: {
              if(_pursue_obj != NULL) {
                _pursue_obj->turn_on();
              }
              break;
            }

    case 4: {
              if(_evade_obj != NULL){
                _evade_obj->turn_on();
              }
              break;
            }

    case 6: {
              if(_flock_obj != NULL) {
                _flock_obj->turn_on();
              }
              break;
            }

    case 7: {
              if(_wander_obj != NULL) {
                _wander_obj->turn_on();
              }
              break;
            }

    case 8: {
              if(_obstacle_avoidance_obj != NULL) {
                _obstacle_avoidance_obj->turn_on();
              }
              break;
            }

    case 9: {
              if(_pursue_obj != NULL && _path_follow_obj != NULL) {
                _pursue_obj->turn_on();
                _path_follow_obj->turn_on();
              }
              break;
            }
    case 16: {
              if(_pursue_obj != NULL && _path_follow_obj != NULL) {
                _pursue_obj->turn_off();
                _path_follow_obj->turn_off();
              }
              break;
            }
    default:
            cout<<"Invalid option!"<<endl;
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : seek
// Description : This function activates seek and makes an object of the Seek class.
//                This is the function we want the user to call for seek to be done.
//                This function is overloaded to accept a NodePath or an LVecBase3f.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::seek(NodePath target_object, float seek_wt) {
  _seek_obj = new Seek(_ai_char, target_object, seek_wt);
  add_objective(_seek_obj);
}

void AIBehaviors::seek(LVecBase3f pos, float seek_wt) {
  _seek_obj = new Seek(_ai_char, pos, seek_wt);
  add_objective(_seek_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function : flee
// Description : This function activates flee_activate and creates an object of the Flee class.
//                This function is overloaded to accept a NodePath or an LVecBase3f.

//////////////////////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::flee(NodePath target_object, double panic_distance, double relax_distance, float flee_wt) {
  SteeringObjective* obj = new Flee(_ai_char, target_object, panic_distance, relax_distance, flee_wt);
  add_to_type( _flee_obj, obj);
}

void AIBehaviors::flee(LVecBase3f pos, double panic_distance, double relax_distance, float flee_wt) {
  SteeringObjective* obj = new Flee(_ai_char, pos, panic_distance, relax_distance, flee_wt);
  add_to_type( _flee_obj, obj);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : pursue
// Description : This function activates pursue.
//                This is the function we want the user to call for pursue to be done.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::pursue(NodePath target_object, float pursue_wt) {
  _pursue_obj = new Pursue(_ai_char, target_object, pursue_wt);
  add_objective(_pursue_obj);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : evade
// Description : This function activates evade_activate.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::evade(NodePath target_object, double panic_distance, double relax_distance, float evade_wt) {
  SteeringObjective* obj = new Evade(_ai_char, target_object, panic_distance, relax_distance, evade_wt);
  add_to_type( _evade_obj, obj);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : flock
// Description : This function activates flock.
//                This is the function we want the user to call for flock to be done.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::flock(float flock_wt) {

  _flock_obj = new FlockObjective(_ai_char, flock_wt);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : wander
// Description : This function activates wander.
//               This is the function we want the user to call for flock to be done.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::wander(double wander_radius, int flag, double aoe, float wander_weight) {
  if (_wander_obj == NULL) {
    _wander_obj = new Wander(_ai_char, wander_radius, flag, aoe, wander_weight);
    add_objective(_wander_obj);
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : obstacle avoidance
// Description : This function activates obstacle avoidance for a given character.
//               This is the function we want the user to call for
//               obstacle avoidance to be performed.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::obstacle_avoidance(float obstacle_avoidance_weight) {
  if (_obstacle_avoidance_obj == NULL) {
    _obstacle_avoidance_obj = new ObstacleAvoidance(_ai_char, obstacle_avoidance_weight);
    add_objective(_obstacle_avoidance_obj);
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : path_follow
// Description : This function activates path following.
//                This is the function we want the user to call for path following.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::path_follow(float follow_wt) {
  if ( _path_follow_obj == NULL) {
    _path_follow_obj = new PathFollow(_ai_char, follow_wt);
    add_objective(_path_follow_obj);
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : add_to_path
// Description : This function adds positions to the path to follow.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::add_to_path(LVecBase3f pos) {
  _path_follow_obj->add_to_path(pos);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : start_follow
// Description : This function starts the path follower.

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::start_follow(string type) {
  _path_follow_obj->start(type);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Function : init_path_find
// Description : This function activates path finding in the character.
//                This function accepts the meshdata in .csv format.
//

/////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::init_path_find(const char* navmesh_filename) {
  _path_find_obj = new PathFind(_ai_char);
  _path_find_obj->set_path_find(navmesh_filename);
}

///////////////////////////////////////////////////////////////////////////////////////
//
// Function : path_find_to (for pathfinding towards a  static position)
// Description : This function checks for the source and target in the navigation mesh
//                for its availability and then finds the best path via the A* algorithm
//                Then it calls the path follower to make the object follow the path.

///////////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::path_find_to(LVecBase3f pos, string type) {
  _path_find_obj->path_find(pos, type);
}

///////////////////////////////////////////////////////////////////////////////////////
//
// Function : path_find_to (for pathfinding towards a moving target (a NodePath))
// Description : This function checks for the source and target in the navigation mesh
//                for its availability and then finds the best path via the A* algorithm
//                Then it calls the path follower to make the object follow the path.

///////////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::path_find_to(NodePath target, string type) {
  _path_find_obj->path_find(target, type);
}

///////////////////////////////////////////////////////////////////////////////////////
//
// Function : add_static_obstacle
// Description : This function allows the user to dynamically add obstacles to the
//                game environment. The function will update the nodes within the
//                bounding volume of the obstacle as non-traversable. Hence will not be
//                considered by the pathfinding algorithm.

///////////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::add_static_obstacle(NodePath obstacle) {
  _path_find_obj->add_obstacle_to_mesh(obstacle);
}

///////////////////////////////////////////////////////////////////////////////////////
//
// Function : add_dynamic_obstacle
// Description : This function starts the pathfinding obstacle navigation for the
//                passed in obstacle.

///////////////////////////////////////////////////////////////////////////////////////

void AIBehaviors::add_dynamic_obstacle(NodePath obstacle) {
  _path_find_obj->dynamic_avoid(obstacle);
}


///////////////////////////////////////////////////////////////////////////////////////
//
// Function : is_on
// Description : This function checks whether an ai objective is active
//
///////////////////////////////////////////////////////////////////////////////////////
bool AIBehaviors::is_on(string ai_type) {
  switch(char_to_int(ai_type)) {
    case 1:
      if(_seek_obj) {
        return _seek_obj->is_on();
      }
      else {
        return false;
      }
      break;

    case 2:
      if(_flee_obj) {
        return _flee_obj->is_on();
      }
      else {
        return false;
      }
      break;

    case 3:
      if(_pursue_obj) {
        return _pursue_obj->is_on();
      }
      else {
        return false;
      }
      break;

    case 4:
      if(_evade_obj) {
        return _evade_obj->is_on();
      }
      else {
        return false;
      }
      break;

    case 6:
      if(_flock_obj) {
        return _flock_obj->is_on();
      }
      else {
        return false;
      }
      break;

    case 7:
      if(_wander_obj) {
        return _wander_obj->is_on();
      }
      else {
        return false;
      }
      break;


      case 8:
        if(_obstacle_avoidance_obj) {
          return _obstacle_avoidance_obj->is_on();
        }
        else {
          return false;
        }
        break;
      case 9:
        if(_path_follow_obj) {
           _path_follow_obj->is_on();
        }
        else {
          return false;
        }
        break;

      case 16:
        if(_path_find_obj) {
          _path_find_obj->is_on();
        }
        else {
          return false;
        }
        break;

      case 10:
        if(! objectives.empty()) {
          return _active;
        }
        else {
          return false;
        }
        break;

      default:
        cout<<"Invalid value!"<<endl;
  
    
  }
  return false;
}

bool AIBehaviors::is_on(SteeringObjective* obj) {
  if (obj != NULL)
    return obj->is_on();
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////
//
// Function : behavior_status
// Description : This function returns the status of an AI Type whether it is active,
//                paused or disabled. It returns -1 if an invalid string is passed.

///////////////////////////////////////////////////////////////////////////////////////

string AIBehaviors::behavior_status(string ai_type) {
  switch(char_to_int(ai_type)) {
    case 1:
      if(_seek_obj) {
        return _seek_obj->behavior_status();
      }
      else {
        return "disabled";
      }
      break;

    case 2:
      if(_flee_obj) {
        return _flee_obj->behavior_status();
      }
      else {
        return "disabled";
      }
      break;

    case 3:
      if(_pursue_obj) {
        return _pursue_obj->behavior_status();
      }
      else {
        return "disabled";
      }
      break;

    case 4:
      if(_evade_obj) {
        return _evade_obj->behavior_status();
      }
      else {
        return "disabled";
      }
      break;

    case 6:
      if(_flock_obj) {
        return _flock_obj->behavior_status();
      }
      else {
          return "disabled";
      }
      break;

    case 7:
      if(_wander_obj) {
        return _wander_obj->behavior_status();
      }
      else {
        return "disabled";
      }
      break;


      case 8:
        if(_obstacle_avoidance_obj) {
          return _obstacle_avoidance_obj->behavior_status();
        }
        else {
          return "disabled";
        }
        break;
      case 9:
        if(_path_follow_obj) {
           _path_follow_obj->behavior_status();
        }
        else {
          return "disabled";
        }
        break;

      case 16:
        if(_path_find_obj) {
          _path_find_obj->behavior_status();
        }
        else {
          return "disabled";
        }
        break;

      case 10:
        if(! objectives.empty()) {
          this->behavior_status();
        }
        else {
          return "disabled";
        }
        break;

      default:
        cout<<"Invalid value!"<<endl;
    }
  }

string AIBehaviors::behavior_status() {
  return Parent::behavior_status();
}
///////////////////////////////////////////////////////////////////////////////////////
//
// Function : char_to_int
// Description : This function is used to derive int values from the ai types strings.
//                Returns -1 if an invalid string is passed.

///////////////////////////////////////////////////////////////////////////////////////

int AIBehaviors::char_to_int(string ai_type) {
  if(ai_type == "all") {
    return 0;
  }
  else if(ai_type == "seek") {
    return 1;
  }
  else if(ai_type == "flee") {
    return 2;
  }
  else if(ai_type == "pursue") {
    return 3;
  }
  else if(ai_type == "evade") {
    return 4;
  }
  else if(ai_type == "arrival") {
    return 5;
  }
  else if(ai_type == "flock") {
    return 6;
  }
  else if(ai_type == "wander") {
    return 7;
  }
  else if(ai_type == "obstacle_avoidance") {
    return 8;
  }
  else if(ai_type == "pathfollow") {
    return 9;
  }
  else if(ai_type == "any") {
    return 10;
  }
  else if(ai_type == "flee_activate") {
    return 11;
  }
  else if(ai_type == "evade_activate") {
    return 12;
  }
  else if(ai_type == "arrival_activate") {
    return 13;
  }
  else if(ai_type == "flock_activate") {
    return 14;
  }
  else if(ai_type == "obstacle_avoidance_activate") {
    return 15;
  }
  else if(ai_type == "path_finding") {
    return 16;
  }

  return -1;
}

