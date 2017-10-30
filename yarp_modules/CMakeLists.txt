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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/btyarpmodule.cpp PARENT_SCOPE)

set(YARP_BT_NODES_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BTCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/btyarpmodule.h PARENT_SCOPE)


set(MYYARP_BT_NODES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BTCmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BlackBoardCmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BlackBoardServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/btyarpmodule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/black_board.cpp)

set(MYYARP_BT_NODES_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BTCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BlackBoardCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BlackBoardServer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/btyarpmodule.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/black_board.h)


#####################################################
#COMPILING RTF Tests
#####################################################
if(RTF_FOUND)
    add_executable(gtests_blackboard src/gtest_blackboard.cpp ${BTSrcLibrary} ${BTHeadLibrary} ${MYYARP_BT_NODES_SOURCES} ${MYYARP_BT_NODES_HEADERS} )
    target_link_libraries(gtests_blackboard ${RTF_LIBRARIES} ${YARP_LIBRARIES})

# add the source codes to build the plugin library
#add_library(gtests_blackboard MODULE ${MYYARP_BT_NODES_SOURCES} ${MYYARP_BT_NODES_HEADERS} include/gtest_blackboard.h src/gtest_blackboard.cpp)
## add required libraries
#target_link_libraries(gtests_blackboard ${RTF_LIBRARIES}
#                                     ${YARP_LIBRARIES}
#                                     )
# set the installation options
install(TARGETS ${PROJECTNAME}
        EXPORT ${PROJECTNAME}
        COMPONENT runtime
        LIBRARY DESTINATION lib)
endif(RTF_FOUND)


add_executable(yarp_module_example ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${MYYARP_BT_NODES_SOURCES} ${MYYARP_BT_NODES_HEADERS})
target_link_libraries(yarp_module_example ${YARP_LIBRARIES})
