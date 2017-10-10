cmake_minimum_required(VERSION 2.8)
project(BTpp)

set(CMAKE_BUILD_TYPE Release)
add_definitions( -Wall -lgtest -std=c++11  -pthread -lrt )
# Needed for using threads
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")



#########################################################
# FIND GTest
#########################################################
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
if(NOT GTEST_FOUND)
    message(WARNING " GTest not found!")
endif(NOT GTEST_FOUND)


#########################################################
# FIND Lua
#########################################################
find_package(Lua REQUIRED)
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})




INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/icons/)


set(BT_CORE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/ PARENT_SCOPE)

INCLUDE_DIRECTORIES(${YARP_BT_NODES_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/gtest/include/)

if(APPLE)
   include_directories(AFTER "/opt/X11/include")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
    if(CMAKE_GENERATOR STREQUAL Xcode)
        set(CMAKE_OSX_DEPLOYMENT_TARGET "10.8")
    endif()
endif()


#file(GLOB_RECURSE BT_CORE_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
#uncomment the above if you want the include files to be shown in you IDE


set(BT_CORE_SOURCES
${PROJECT_SOURCE_DIR}/src/action_node.cpp
${PROJECT_SOURCE_DIR}/src/behavior_tree.cpp
${PROJECT_SOURCE_DIR}/src/condition_node.cpp
${PROJECT_SOURCE_DIR}/src/control_node.cpp
${PROJECT_SOURCE_DIR}/src/exceptions.cpp
${PROJECT_SOURCE_DIR}/src/leaf_node.cpp
${PROJECT_SOURCE_DIR}/src/tick_engine.cpp
${PROJECT_SOURCE_DIR}/src/parallel_node.cpp
${PROJECT_SOURCE_DIR}/src/fallback_node.cpp
${PROJECT_SOURCE_DIR}/src/sequence_node.cpp
${PROJECT_SOURCE_DIR}/src/fallback_node_with_memory.cpp
${PROJECT_SOURCE_DIR}/src/sequence_node_with_memory.cpp
${PROJECT_SOURCE_DIR}/src/tree_node.cpp
${PROJECT_SOURCE_DIR}/src/yarp_nodes/yarp_action_node.cpp
${PROJECT_SOURCE_DIR}/src/yarp_nodes/yarp_condition_node.cpp
${PROJECT_SOURCE_DIR}/src/lua_action_node.cpp
${PROJECT_SOURCE_DIR}/src/lua_condition_node.cpp
)


######################################################
# SETTING BINARIES AND LIBRARY OUTPUT LOCATIONS
######################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sample)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

######################################################
# COMPILING GTEST
######################################################
if(GTEST_FOUND)
    add_executable(btpp_gtest gtest/gtest_tree.cpp ${BTSrcLibrary} ${BTHeadLibrary})
    target_link_libraries(btpp_gtest  ${OPENGL_LIBRARIES} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
endif(GTEST_FOUND)



add_executable(example src/example.cpp ${BT_CORE_SOURCES}  ${YARP_BT_NODES_SOURCES})
target_link_libraries(example ${YARP_LIBRARIES} ${LUA_LIBRARIES})


#######################################################
## COMPILING LIBRARY
#######################################################
add_library(BT_CORE_LIBRARY ${BT_CORE_SOURCES}  ${YARP_BT_NODES_SOURCES})

target_include_directories (BT_CORE_LIBRARY PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(BT_CORE_LIBRARY ${LUA_LIBRARIES})

#######################################################
## INSTALLATION OF LIBRARY
#######################################################
#install(TARGETS BTpp
#        EXPORT  btpp-targets
#        DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
#)









#project(YARPBTCORE)


#find_package(YARP REQUIRED)


#set(CMAKE_BUILD_TYPE Release)

#INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS})
# ADD_DEFINITIONS(${YARP_DEFINES}) # optional
# # pick up YARP find scripts
# SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


#include_directories(${YARP_BT_NODES_INCLUDE_DIRS})

#include_directories(${YARP_DIR}/include)
#include_directories(${YARP_DIR}/lib)

#set(BT_CORE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/ PARENT_SCOPE)



#file(GLOB_RECURSE BTHeadLibrary ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h )


#set(BTSrcLibrary
#${CMAKE_CURRENT_SOURCE_DIR}/src/action_node.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/behavior_tree.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/condition_node.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/control_node.cpp
##src/draw.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/leaf_node.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/tick_engine.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/parallel_node.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/fallback_node.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/sequence_node.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/fallback_node_with_memory.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/sequence_node_with_memory.cpp
##src/decorator_sync.cpp

#${CMAKE_CURRENT_SOURCE_DIR}/src/tree_node.cpp

##${CMAKE_CURRENT_SOURCE_DIR}/gtest/src/action_test_node.cpp
##${CMAKE_CURRENT_SOURCE_DIR}/gtest/src/condition_test_node.cpp

#${CMAKE_CURRENT_SOURCE_DIR}/src/yarp_nodes/yarp_condition_node.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/yarp_nodes/yarp_action_node.cpp
#)


#######################################################
## SETTING BINARIES AND LIBRARY OUTPUT LOCATIONS
#######################################################
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sample)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

########################################################
### COMPILING GTEST
########################################################
##if(GTEST_FOUND)
##    add_executable(btpp_gtest gtest/gtest_tree.cpp ${BTSrcLibrary} ${BTHeadLibrary})
##    target_link_libraries(btpp_gtest  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}  ${X11_LIBRARIES} ${YARP_LIBRARIES} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${Boost_LIBRARIES} rt)
##endif(GTEST_FOUND)

########################################################
### COMPILING LIBRARY
########################################################
#add_library(BT_CORE_LIBRARY ${BT_CORE_SOURCES})

#target_include_directories (BT_CORE_LIBRARY PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(BT_CORE_LIBRARY ${LUA_LIBRARIES})
