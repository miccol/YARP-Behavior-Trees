# pick up YARP find scripts
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
#compile definition file to generate source code into the desired directory
set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(BTCmd.thrift ${generated_libs_dir} sources headers include_dirs)
# generated source files now listed in ${sources}
# generated header files now listed in ${headers}

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)


#########################################################
# FIND GTest
#########################################################

###Looks for env variables for GTest (Useful in Windows 10)
if (NOT "$ENV{GTEST_LIBRARY}" STREQUAL "")
    set(GTEST_LIBRARY "$ENV{GTEST_LIBRARY}" CACHE INTERNAL "Copied from environment variable")
endif()

if (NOT "$ENV{GTEST_INCLUDE_DIR}" STREQUAL "")
    set(GTEST_INCLUDE_DIR "$ENV{GTEST_INCLUDE_DIR}" CACHE INTERNAL "Copied from environment variable")
endif()

if (NOT "$ENV{GTEST_MAIN_LIBRARY}" STREQUAL "")
    set(GTEST_MAIN_LIBRARY "$ENV{GTEST_MAIN_LIBRARY}" CACHE INTERNAL "Copied from environment variable")
endif()

find_package(GTest REQUIRED)
if(NOT GTEST_FOUND)
    message(WARNING " GTest not found!")
endif(NOT GTEST_FOUND)

include_directories(${GTEST_INCLUDE_DIRS})

message("GTEST_INCLUDE_DIRS" ${GTEST_INCLUDE_DIRS} )

set(YARP_BT_NODES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ PARENT_SCOPE)

set(YARP_BT_NODES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BTCmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/btyarpmodule.cpp PARENT_SCOPE)

set(YARP_BT_NODES_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BTCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/btyarpmodule.h PARENT_SCOPE)


set(MYYARP_BT_NODES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BTCmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/btyarpmodule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/black_board.cpp)

set(MYYARP_BT_NODES_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BTCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/btyarpmodule.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/black_board.h)

######################################################
# COMPILING GTEST
######################################################
if(GTEST_FOUND)
    add_executable(gtests_blackboard gtest_blackboard.cpp ${BTSrcLibrary} ${BTHeadLibrary})
    target_link_libraries(gtests_blackboard ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
endif(GTEST_FOUND)


add_executable(yarp_module_example ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${MYYARP_BT_NODES_SOURCES} ${MYYARP_BT_NODES_HEADERS})
target_link_libraries(yarp_module_example ${YARP_LIBRARIES})
