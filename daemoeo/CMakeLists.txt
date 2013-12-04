CMAKE_MINIMUM_REQUIRED(VERSION 2.8)



#OPTION (DAE-YASHP  "DAE-YASHP" ON)

IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

# include the install configuration file where are defined the main variables


# define project name
PROJECT(DAEXMOEO)

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/install.cmake)
# include useful features for cmake
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules) 

# IF (WITH_OPENMP)
 FIND_PACKAGE(OpenMP REQUIRED)

 IF(OPENMP_FOUND)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
   SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  ENDIF()
 # ENDIF()

 
 

#IF(DAE-YASHP)
 #   ADD_DEFINITIONS(-DDAE)
#ENDIF(DAE-YASHP)

# include the sources
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src_cpt
  ${CMAKE_CURRENT_SOURCE_DIR}/src_daex
  ${DAEXMOEO_SRC_DIR}/src/core
  ${DAEXMOEO_SRC_DIR}/src/do
  ${DAEXMOEO_SRC_DIR}
  ${DAEX_DIR}
  ${DAEX_DIR}/core
  ${DAEX_DIR}/utils
  ${DAEX_DIR}/pack
  ${DAEX_DIR}/initialization
  ${DAEX_DIR}/evaluation
  ${DAEX_DIR}/variation	
  ${PARADISEO_EO_SRC_DIR}/src 
  ${PARADISEO_MO_SRC_DIR}/src  
  ${PARADISEO_MOEO_SRC_DIR}/src 
  ${PARADISEO_PEO_SRC_DIR}/src
  ${CPT_YAHSP_SRC_DIR}
  ${GDSL_LIBRARY}   
  )




# where CMake can find the libraries
LINK_DIRECTORIES(
  ${GDSL_LIBRARY}
  ${CPT_YAHSP_DIR}/lib
  ${DAEX_DIR}/lib}
  ${DAEXMOEO_SRC_DIR}/lib}

  )

# Link with the EO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_EO_BIN_DIR}/lib)

LINK_DIRECTORIES(${PARADISEO_MO_BIN_DIR}/lib)

# Link with the MOEO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_MOEO_BIN_DIR}/lib)

# Link with the PEO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_PEO_BIN_DIR}/lib)

LINK_DIRECTORIES(${PARADISEO_DIR}/libxml2/lib)

LINK_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/src_daex/lib)


# flags to use with compiler
# VV : -DDAE pour les headers de YAHSP
ADD_DEFINITIONS(-W -Wall -DDAE )#-DCOST_ADD) 

IF (CMAKE_BUILD_TYPE MATCHES Debug)
  #ADD_DEFINITIONS(-DPAPERVERSION)
  ADD_DEFINITIONS(-pg -g)
ELSE()
  ADD_DEFINITIONS(-O3 -DNDEBUG)
ENDIF()

 
# target + link libraries

LINK_LIBRARIES( daex  daexmoeo eoutils gmp  rt ncurses eo gcov gdsl)

ADD_EXECUTABLE(daemoeo daemoeo.cpp) 
ADD_DEPENDENCIES(daemoeo daex daexmoeo moeo)
TARGET_LINK_LIBRARIES(daemoeo moeo  eoutils gmp eo gcov gdsl  cpt_yahsp_library-common-dae-omp    cpt_yahsp_library-dae  daex daexmoeo )

ADD_EXECUTABLE(daensgaII daensgaII.cpp) 
ADD_DEPENDENCIES(daensgaII daex daexmoeo moeo)
TARGET_LINK_LIBRARIES(daensgaII moeo  eoutils gmp eo gcov gdsl  cpt_yahsp_library-common-dae-omp    cpt_yahsp_library-dae  daex daexmoeo )



ADD_EXECUTABLE(daeibea daeibea.cpp) 
ADD_DEPENDENCIES(daeibea daex daexmoeo moeo)
TARGET_LINK_LIBRARIES(daeibea moeo  eoutils gmp eo gcov gdsl  cpt_yahsp_library-common-dae-omp    cpt_yahsp_library-dae  daex daexmoeo )




ADD_EXECUTABLE(daespeaII daespeaII.cpp) 
ADD_DEPENDENCIES(daespeaII daex daexmoeo moeo)
TARGET_LINK_LIBRARIES(daespeaII moeo  eoutils gmp eo gcov gdsl  cpt_yahsp_library-common-dae-omp    cpt_yahsp_library-dae  daex daexmoeo )


#TARGET_LINK_LIBRARIES(daemoeo moeo  eoutils gmp eo gcov gdsl   cpt_yahsp_library-common-dae-noomp  cpt_yahsp_library-dae-noomp  daex daexmoeo )
 #  1 cpt_yahsp_library-common cpt_yahsp_library-dae 
# 2 cpt_yahsp_library-common-dae-omp    cpt_yahsp_library-dae daex
 
ADD_SUBDIRECTORY(src)
