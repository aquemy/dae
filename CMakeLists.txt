######################################################################################
### 0) Project definition
######################################################################################
cmake_minimum_required(VERSION 2.8)
project(DESCARWIN)

# include the install configuration file where are defined the main variables
include(${CMAKE_SOURCE_DIR}/install.cmake OPTIONAL)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# TESTS
if(ENABLE_CMAKE_TESTING)
    enable_testing()
    include(CTest REQUIRED)
endif()
#

if(WITH_OMP)
    set(CPT_WITH_OMP "true" CACHE BOOL "Build a parallel YAHSP with OpenMP (shared memory)")
    set(DAE_WITH_OMP "true" CACHE BOOL "Build a parallel DAE with OpenMP (shared memory)")
endif()

if(WITH_MPI)
    set(CPT_WITH_MPI "true" CACHE BOOL "Build a parallel YAHSP with MPI (message passing)")
    set(DAE_WITH_MPI "true" CACHE BOOL "Build a parallel DAE with MPI (message passing)")
endif()

set(BUILD_DAE_MO "true" CACHE BOOL "Build the Multi-Objective version of DAE")

######################################################################################
### 1) Dependencies
######################################################################################
# Include ParadisEO
find_package(Paradiseo COMPONENTS eo eoutils moeo REQUIRED)
include_directories(${PARADISEO_INCLUDE_DIR})

# the source directory of yahsp is not /src/ because we include src/cpt.h instead of cpt.h
# because of name collisions
set(DAE true) # YAHSP CONFIGURATION
set(CPT_YAHSP_SRC_DIR ${CMAKE_SOURCE_DIR}/cpt-yahsp)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CPT_YAHSP_BIN_DIR "${LIBRARY_OUTPUT_PATH}")

include_directories(cpt-yahsp)
include_directories(src/)

link_directories(${PARADISEO_ROOT}/build/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)

######################################################################################
### 2) DAEX Config
######################################################################################
set(DAEX_SRC_DIR "${CMAKE_SOURCE_DIR}/dae/src")
set(DAEXMOEO_SRC_DIR "${CMAKE_SOURCE_DIR}/dae/src")

######################################################################################
### 3) Include subdirectories
######################################################################################
add_subdirectory(cpt-yahsp)
add_subdirectory(dae)


