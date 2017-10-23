cmake_minimum_required(VERSION 2.8)

project(BTYARP)

# Enable C++11
include(CheckCXXCompilerFlag)
unset(CXX11_FLAGS)
check_cxx_compiler_flag("-std=c++11" CXX_HAS_STD_CXX11)
if(CXX_HAS_STD_CXX11)
  set(CXX11_FLAGS "-std=c++11")
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
if(NOT CMAKE_MINIMUM_REQUIRED_VERSION VERSION_LESS 3.1)
  message(AUTHOR_WARNING "CMAKE_MINIMUM_REQUIRED_VERSION is now ${CMAKE_MINIMUM_REQUIRED_VERSION}. This check can be removed.")
endif()
if(${CMAKE_VERSION} VERSION_LESS 3.1)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")
endif()



#########################################################
# FIND YARP
#########################################################

find_package(YARP REQUIRED)
INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS})
 ADD_DEFINITIONS(${YARP_DEFINES}) # optional

 # pick up YARP find scripts
 SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})

add_subdirectory(yarp_modules)

add_subdirectory(core)

add_subdirectory(editor)
