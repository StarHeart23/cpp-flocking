cmake_minimum_required(VERSION 3.7)
project(cpp_flocking)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h
        GLMath.cpp GLMath.h
        GLVector.cpp GLVector.h
        GLPath.cpp GLPath.h
        GameEntity.cpp GameEntity.h
        GameWorld.cpp GameWorld.h
        GLFloor.cpp GLFloor.h
        GLQuadTree_Node.cpp GLQuadTree_Node.h
        GLQuadTree.cpp GLQuadTree.h
        GLRole.cpp GLRole.h
        GLRole_Predator.cpp GLRole_Predator.h
        GLRole_Prey.cpp GLRole_Prey.h
        GLRole_Unknown.cpp GLRole_Unknown.h
        GLSteering.cpp GLSteering.h
        GLSteering_Alignment.cpp GLSteering_Alignment.h
        GLSteering_Avoidance.cpp GLSteering_Avoidance.h
        GLSteering_Cohesion.cpp GLSteering_Cohesion.h
        GLSteering_Composite.cpp GLSteering_Composite.h
        GLSteering_Evade.cpp GLSteering_Evade.h
        GLSteering_Flee.cpp GLSteering_Flee.h
        GLSteering_Interpose.cpp GLSteering_Interpose.h
        GLSteering_OffsetPursuit.cpp GLSteering_OffsetPursuit.h
        GLSteering_PathFollow.cpp GLSteering_PathFollow.h
        GLSteering_Pursuit.cpp GLSteering_Pursuit.h
        GLSteering_Seek.cpp GLSteering_Seek.h
        GLSteering_Separation.cpp GLSteering_Separation.h
        GLSteering_Wander.cpp GLSteering_Wander.h
        MovingEntity.cpp MovingEntity.h
        Obstacle.cpp Obstacle.h
        Vehicle.cpp Vehicle.h
        )
add_library(cpp_flocking ${SOURCE_FILES})