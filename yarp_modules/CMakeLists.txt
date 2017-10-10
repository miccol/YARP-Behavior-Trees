# pick up YARP find scripts
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
#compile definition file to generate source code into the desired directory
set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(BTCmd.thrift ${generated_libs_dir} sources headers include_dirs)
# generated source files now listed in ${sources}
# generated header files now listed in ${headers}

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(YARP_BT_NODES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ PARENT_SCOPE)

set(YARP_BT_NODES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BTCmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/btyarpmodule.cpp PARENT_SCOPE)

set(YARP_BT_NODES_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BTCmd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/btyarpmodule.h PARENT_SCOPE)


#set(MYYARP_BT_NODES_SOURCES
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/BTCmd.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/btyarpmodule.cpp)

#set(MYYARP_BT_NODES_HEADERS
#    ${CMAKE_CURRENT_SOURCE_DIR}/include/BTCmd.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/include/btyarpmodule.h)


#add_executable(yarp_module_example ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${MYYARP_BT_NODES_SOURCES} ${MYYARP_BT_NODES_HEADERS})
#target_link_libraries(yarp_module_example ${YARP_LIBRARIES})
