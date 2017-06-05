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
        )
add_library(cpp_flocking ${SOURCE_FILES})