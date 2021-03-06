cmake_minimum_required(VERSION 2.8.3)
project(autotune)

#####################
## Compile Setting ##
#####################

add_compile_options(-std=c++17)

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -Wno-unused-variable -pthread")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -pthread -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )
message("Build Type:" ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})

##########################
## Dependencies Setting ##
##########################

set(${PROJECT_NAME}_DEPS
  nox
)

set(${PROJECT_NAME}_SYSTEM_DEPS
)

find_package(catkin REQUIRED COMPONENTS
  ${${PROJECT_NAME}_DEPS}
  ${${PROJECT_NAME}_SYSTEM_DEPS}
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

################################################
## Declare ROS messages, services and actions ##
################################################

#add_message_files(
#        FILES
#
#)

#generate_messages(
#        DEPENDENCIES
#        std_msgs
#)

###################################
## catkin specific configuration ##
###################################

set(${PROJECT_NAME}_PLUGINS
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${${PROJECT_NAME}_PLUGINS}
  CATKIN_DEPENDS ${${PROJECT_NAME}_DEPS}
  DEPENDS ${${PROJECT_NAME}_SYSTEM_DEPS}
)

######################
## Build Executable ##
######################
#pragma nox_begin("build executable")
add_executable(Planner
    include/Planner/.PlannerModule.h src/Planner/.PlannerModule.cpp
    include/Planner/Planner.h src/Planner/Planner.cpp
        include/Planner/type/ReferenceLine.h include/Planner/tool/TrajectoryStitcher.h src/Planner/tool/TrajectoryStitcher.cpp include/Planner/tool/DecisionMaker.h src/Planner/tool/DecisionMaker.cpp include/Planner/tool/TrafficDecider.h src/Planner/tool/TrafficDecider.cpp include/Planner/rule/Junction.h src/Planner/rule/Junction.cpp include/Planner/rule/SignalLight.h src/Planner/rule/SignalLight.cpp include/Planner/rule/Overtake.h src/Planner/rule/Overtake.cpp src/Planner/type/ReferenceLine.cpp include/Planner/impl/PlannerBase.h src/Planner/impl/PlannerBase.cpp include/Planner/impl/LatticePlanner.h src/Planner/impl/LatticePlanner.cpp include/Planner/type/SLTBoundary.h include/Planner/type/STGraph.h src/Planner/type/STGraph.cpp include/Planner/tool/lattice/LatticeGenerator.h src/Planner/tool/lattice/LatticeGenerator.cpp include/Planner/tool/lattice/LatticeSampler.h include/Planner/tool/lattice/LatticeCommon.h src/Planner/tool/lattice/LatticeCommon.cpp src/Planner/tool/lattice/LatticeSampler.cpp include/Planner/type/FeasibleRegion.h src/Planner/type/FeasibleRegion.cpp include/Planner/PlannerConfig.h include/Planner/tool/PredictionQuerier.h src/Planner/tool/PredictionQuerier.cpp include/Planner/tool/lattice/LatticeEvaluator.h src/Planner/tool/lattice/LatticeEvaluator.cpp include/Planner/type/ConstantAccelerationCurve.h src/Planner/type/ConstantAccelerationCurve.cpp include/Planner/tool/ConstraintChecker.h src/Planner/tool/ConstraintChecker.cpp include/Planner/tool/CollisionChecker.h src/Planner/tool/CollisionChecker.cpp)
target_link_libraries(Planner
    ${catkin_LIBRARIES}
)
set_target_properties(Planner PROPERTIES OUTPUT_NAME Planner PREFIX "")
set_target_properties(Planner PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../.bin/autotune/)

add_executable(LoMap
    include/LoMap/.LoMapModule.h src/LoMap/.LoMapModule.cpp
    include/LoMap/LoMap.h src/LoMap/LoMap.cpp
        include/LoMap/tool/SceneMaintainer.h include/LoMap/tool/PoseEstimator.h src/LoMap/tool/PoseEstimator.cpp include/LoMap/tool/StaticSceneUpdater.h src/LoMap/tool/StaticSceneUpdater.cpp include/LoMap/tool/IDProvider.h src/LoMap/tool/IDProvider.cpp include/LoMap/tool/SceneObjectCreator.h include/LoMap/tool/DynamicSceneUpdater.h src/LoMap/tool/DynamicSceneUpdater.cpp src/LoMap/tool/SceneMaintainer.cpp include/LoMap/tool/SceneOverlapBuilder.h src/LoMap/tool/SceneOverlapBuilder.cpp)
target_link_libraries(LoMap
    ${catkin_LIBRARIES}
)
set_target_properties(LoMap PROPERTIES OUTPUT_NAME LoMap PREFIX "")
set_target_properties(LoMap PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../.bin/autotune/)


#pragma nox_end()
#################################
## Build Plugin Inplementation ##
#################################
#pragma nox_begin("build plugin")


#pragma nox_end()
