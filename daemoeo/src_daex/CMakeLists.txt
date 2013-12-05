# include the sources

#INCLUDE_DIRECTORIES(${EO_SRC_DIR}/src)
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# target the dae lib


# flags to use with compiler
# VV : -DDAE pour les headers de YAHSP
 ADD_DEFINITIONS(-W -Wall -DDAE) 


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

ADD_LIBRARY(daex STATIC ${DAEXLB_SOURCES})

TARGET_LINK_LIBRARIES( daex cpt_yahsp_library eo eoutils )
#TARGET_LINK_LIBRARIES( daex  cpt_yahsp_library-common-dae-omp  cpt_yahsp_library-dae eo eoutils )

#TARGET_LINK_LIBRARIES( daex  cpt_yahsp_library-common-dae-noomp  cpt_yahsp_library-dae-noomp eo eoutils )
 
SET_TARGET_PROPERTIES(daex PROPERTIES LINKER_LANGUAGE CXX)

