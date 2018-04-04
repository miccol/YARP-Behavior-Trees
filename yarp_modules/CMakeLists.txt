# pick up YARP find scripts
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
#compile definition file to generate source code into the desired directory
set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(BTCmd.thrift ${generated_libs_dir} sources headers include_dirs)

set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(BlackBoardCmd.thrift ${generated_libs_dir} sources headers include_dirs)

# generated source files now listed in ${sources}
# generated header files now listed in ${headers}

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)


#########################################################
# FIND RTF (Optional For testing)
#########################################################
find_package(RTF)
find_package(RTF COMPONENTS DLL)
if(NOT RTF_FOUND)
    message(WARNING " RTF not found!")
endif(NOT RTF_FOUND)

find_package(YARP)

include_directories(${CMAKE_SOURCE_DIR}
                    ${RTF_INCLUDE_DIRS}
                    ${YARP_INCLUDE_DIRS})

set(YARP_BT_NODES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ PARENT_SCOPE)

set(YARP_BT_NODES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BTCmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/yarp_bt_module.cpp PARENT_SCOPE)

set(YARP_BT_NODES_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BTCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/yarp_bt_module.h PARENT_SCOPE)


set(MYYARP_BT_NODES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BTCmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BlackBoardCmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/blackboard_server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/yarp_bt_module.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/blackboard.cpp)

set(MYYARP_BT_NODES_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BTCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BlackBoardCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/blackboard_server.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/yarp_bt_module.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/blackboard.h)


#####################################################
#COMPILING RTF Tests
#####################################################
if(RTF_FOUND)
#    add_executable(tests_blackboard src/test_blackboard.cpp ${BTSrcLibrary} ${BTHeadLibrary} ${MYYARP_BT_NODES_SOURCES} ${MYYARP_BT_NODES_HEADERS} )
#    target_link_libraries(tests_blackboard ${RTF_LIBRARIES} ${YARP_LIBRARIES})
endif(RTF_FOUND)


add_executable(yarp_module_example ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${MYYARP_BT_NODES_SOURCES} ${MYYARP_BT_NODES_HEADERS})
target_link_libraries(yarp_module_example ${YARP_LIBRARIES})
