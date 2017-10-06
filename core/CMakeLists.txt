
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


include_directories(${YARP_BT_NODES_INCLUDE_DIRS})




file(GLOB_RECURSE BTHeadLibrary ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h )


set(BTSrcLibrary
${CMAKE_CURRENT_SOURCE_DIR}/src/action_node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/behavior_tree.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/condition_node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/control_node.cpp
#src/draw.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/leaf_node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/tick_engine.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/parallel_node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/fallback_node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/sequence_node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/fallback_node_with_memory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/sequence_node_with_memory.cpp
#src/decorator_sync.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/tree_node.cpp

#${CMAKE_CURRENT_SOURCE_DIR}/gtest/src/action_test_node.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/gtest/src/condition_test_node.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/yarp_nodes/yarp_condition_node.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/yarp_nodes/yarp_action_node.cpp
)


######################################################
# SETTING BINARIES AND LIBRARY OUTPUT LOCATIONS
######################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sample)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#######################################################
## COMPILING GTEST
#######################################################
#if(GTEST_FOUND)
#    add_executable(btpp_gtest gtest/gtest_tree.cpp ${BTSrcLibrary} ${BTHeadLibrary})
#    target_link_libraries(btpp_gtest  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}  ${X11_LIBRARIES} ${YARP_LIBRARIES} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${Boost_LIBRARIES} rt)
#endif(GTEST_FOUND)

######################################################
# COMPILING SAMPLE EXAMPLE
######################################################
add_executable(btpp_example ${CMAKE_CURRENT_SOURCE_DIR}/src/example.cpp ${BTSrcLibrary} ${BTHeadLibrary} ${YARP_BT_NODES_SOURCES} ${YARP_BT_NODES_HEADERS})
target_link_libraries(btpp_example ${YARP_LIBRARIES} )


#######################################################
## COMPILING Synchronization EXAMPLE
#######################################################
#add_executable(btpp_sync_example src/example_sync.cpp ${BTSrcLibrary} ${BTHeadLibrary})
#target_link_libraries(btpp_sync_example  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${X11_LIBRARIES} ${YARP_LIBRARIES} ${Boost_LIBRARIES} rt)


#######################################################
## COMPILING LIBRARY
#######################################################
#add_library(btpp SHARED ${BTSrcLibrary} ${BTHeadLibrary})
#target_link_libraries(btpp ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${X11_LIBRARIES} ${YARP_LIBRARIES} ${Boost_LIBRARIES} rt )

#######################################################
## INSTALLATION OF LIBRARY AND EXECUTABLE TO /usr/local
#######################################################
#install(TARGETS btpp
#        EXPORT btpp-targets
#        DESTINATION lib
#)

#install(FILES ${BTHeadLibrary} DESTINATION include/)

message("YARP_BT_NODES_INCLUDE_DIRS: " ${YARP_BT_NODES_INCLUDE_DIRS} "-------------------------------------")

