######################################################################################
### 0) Project definition
######################################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(DESCARWIN)

# Note: toplevel definition, because it is used also for dae
set(CPT_WITH_OMP "off" CACHE BOOL "Build a parallel YAHSP with OpenMP (shared memory)")
set(CPT_WITH_MPI "off" CACHE BOOL "Build a parallel YAHSP with MPI (message passing)")

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

# include the install configuration file where are defined the main variables
INCLUDE(${CMAKE_SOURCE_DIR}/install.cmake OPTIONAL)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# TESTS
set(ENABLE_CMAKE_TESTING "True")
enable_testing()
include(CTest REQUIRED)

#

######################################################################################
### 0) Dependencies
######################################################################################
# Include ParadisEO
find_package(Paradiseo COMPONENTS eo eoutils moeo REQUIRED)
include_directories(${PARADISEO_INCLUDE_DIR})

# the source directory of yahsp is not /src/ because we include src/cpt.h instead of cpt.h
# because of name collisions
set(CPT_YAHSP_SRC_DIR ${CMAKE_SOURCE_DIR}/cpt-yahsp)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
SET(CPT_YAHSP_BIN_DIR "${LIBRARY_OUTPUT_PATH}")
include_directories(cpt-yahsp)
include_directories(src/)
LINK_DIRECTORIES(${PARADISEO_ROOT}/build/lib)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)
######################################################################################
### 0) DAEX Config
######################################################################################
set(DAEX_SRC_DIR "${CMAKE_SOURCE_DIR}/dae/src_daex")
set(DAEXMOEO_SRC_DIR "${CMAKE_SOURCE_DIR}/dae/src")

######################################################################################
### Include subdirectories
######################################################################################
ADD_SUBDIRECTORY(cpt-yahsp)
ADD_SUBDIRECTORY(dae)


