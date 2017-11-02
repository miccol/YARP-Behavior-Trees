cmake_minimum_required(VERSION 2.8)

project(YARPBT)

#########################################################
# Enable C++11
#########################################################
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

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR ${PROJECT_BINARY_DIR}/lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR ${PROJECT_BINARY_DIR}/bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR ${PROJECT_BINARY_DIR}/CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR ${PROJECT_BINARY_DIR}/lib/CMake/FooBar)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")


#########################################################
# Make relative paths absolute (needed later on)
#########################################################

foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()


add_subdirectory(yarp_modules)

add_subdirectory(core)

add_subdirectory(editor)


set(INSTALL_CMAKE_DIR ${PROJECT_BINARY_DIR}/install)



#########################################################
# INSTALLATION OF THE LIBRARY
#########################################################


