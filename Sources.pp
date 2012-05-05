#define LOCAL_LIBS p3contribbase
#define BUILDING_DLL BUILDING_PANDAAI

#define OTHER_LIBS \
   panda:c \
   p3express:c p3putil:c p3pandabase:c pandaexpress:m \
   p3interrogatedb:c p3prc:c p3dconfig:c p3dtoolconfig:m \
   p3dtoolutil:c p3dtoolbase:c p3dtool:m

#begin lib_target
  #define TARGET pandaai

  #define COMBINED_SOURCES p3ai_composite1.cxx

  #define SOURCES \
    aiBehaviors.h \
    aiCharacter.h \
    aiGlobals.h \
    aiNode.h \
    aiPathFinder.h \
    aiWorld.h \
    config_ai.h \
    evade.h \
    flee.h \
    flock.h \
    flockObjective.h \
    intercept.h \
    meshNode.h \
    objectiveList.h \
    obstacleAvoidance.h \
    pathFind.h \
    pathFollow.h \
    pursue.h \
    seek.h \
    steeringObjective.h \
    wander.h

  #define INCLUDED_SOURCES \
    aiBehaviors.cxx \
    aiCharacter.cxx \
    aiNode.cxx \
    aiPathFinder.cxx \
    aiWorld.cxx \
    p3ai_composite.cxx \
    p3ai_composite1.cxx \
    config_ai.cxx \
    evade.cxx \
    flee.cxx \
    flock.cxx \
    flockObjective.cxx \
    intercept.cxx \
    meshNode.cxx \
    objectiveList.cxx \
    obstacleAvoidance.cxx \
    pathFind.cxx \
    pathFollow.cxx \
    pursue.cxx \
    seek.cxx \
    steeringObjective.cxx \
    wander.cxx


  #define INSTALL_HEADERS \
    aiBehaviors.h \
    aiCharacter.h \
    aiGlobals.h \
    aiNode.h \
    aiPathFinder.h \
    aiWorld.h \
    config_ai.h \
    evade.h \
    flee.h \
    flock.h \
    flockObjective.h \
    intercept.h \
    meshNode.h \
    objectiveList.h \
    obstacleAvoidance.h \
    pathFind.h \
    pathFollow.h \
    pursue.h \
    seek.h \
    steeringObjective.h \
    wander.h

  #define IGATESCAN all

#end lib_target

