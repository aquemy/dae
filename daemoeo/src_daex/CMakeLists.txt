# include the sources

#INCLUDE_DIRECTORIES(${EO_SRC_DIR}/src)
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# target the dae lib

 
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_LANGUAGE(CXX) 


# flags to use with compiler
# VV : -DDAE pour les headers de YAHSP
 ADD_DEFINITIONS(-W -Wall -DDAE) 
 



PROJECT(DAEXLB)


 

# include the install configuration file where are defined the main variables
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/install.cmake)

SET(DAEXLB_LIB_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
SET(LIBRARY_OUTPUT_PATH ${DAEXLB_LIB_OUTPUT_PATH})

SET(PARADISEO_DIR "/users/tao/khouadjia/paradiseo-1.2.1" CACHE PATH "ParadisEO directory" FORCE)
SET(PARADISEO_EO_SRC_DIR "${PARADISEO_DIR}/paradiseo-eo" CACHE PATH "ParadisEO-EO source directory" FORCE)
SET(PARADISEO_EO_BIN_DIR "${PARADISEO_DIR}/paradiseo-eo/build" CACHE PATH "ParadisEO-EO binary directory" FORCE)

#SET (DAEXLB_SOURCE_DIR "/home/mustapha/framework/dae/descarwin/trunk/daemoeo/src_daex"  CACHE PATH "DAEX_LIB directory" FORCE)


SET (DAEXLB_SOURCES
  utils/posix_timer.cpp
  utils/pddl_load.h
  utils/pddl_load.cpp
  #utils/evalBestPlanDump.cpp
  core/decomposition.cpp
  core/goal.cpp
  initialization/init.h
  evaluation/cpt-yahsp.h # evaluation/cpt-yahsp.cpp
  evaluation/yahsp.h  #evaluation/yahsp.cpp
  variation/addgoal.h
  variation/delgoal.h
  variation/delatom.h
  variation/crossover.h ) 


INCLUDE_DIRECTORIES(
		    ${PARADISEO_EO_SRC_DIR}/src 
                    ${PARADISEO_MO_SRC_DIR}/src
                    ${PARADISEO_MOEO_SRC_DIR}/src
                    ${PARADISEO_PEO_SRC_DIR}/src	
		    ${CPT_YAHSP_SRC_DIR}
		    ${GDSL_LIBRARY}	
 		    ${DAEXLB_SOURCE_DIR}/utils		    
		    ${DAEXLB_SOURCE_DIR}/core
		    ${DAEXLB_SOURCE_DIR}/pack
	  	    ${DAEXLB_SOURCE_DIR}/initialization
    		    ${DAEXLB_SOURCE_DIR}/evaluation
 		    ${DAEXLB_SOURCE_DIR}/variation
		    ${DAEXLB_SOURCE_DIR})


#		   
######################################################################################


######################################################################################
###  Specify where CMake can find the libraries
######################################################################################

# Link with the EO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_EO_BIN_DIR}/lib)

# Link with the MOEO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_MOEO_BIN_DIR}/lib)

# Link with the PEO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_PEO_BIN_DIR}/lib)

LINK_DIRECTORIES(${PARADISEO_DIR}/libxml2/lib)

LINK_DIRECTORIES(${DAEXLB_BIN_DIR}/lib
		 ${GDSL_LIBRARY}
		 ${CPT_YAHSP_DIR}/lib)
#		 ${DAE_BIN_DIR})

ADD_LIBRARY(daex STATIC ${DAEXLB_SOURCES})

TARGET_LINK_LIBRARIES( daex  cpt_yahsp_library-common-dae-omp  cpt_yahsp_library-dae eo eoutils )

#TARGET_LINK_LIBRARIES( daex  cpt_yahsp_library-common-dae-noomp  cpt_yahsp_library-dae-noomp eo eoutils )
 
SET_TARGET_PROPERTIES(daex PROPERTIES LINKER_LANGUAGE CXX)

