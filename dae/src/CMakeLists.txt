add_definitions(-W -Wall -DDAE) 


set(DAEX_SRC
    ${DAEX_SRC_DIR}/utils/posix_timer.cpp
    ${DAEX_SRC_DIR}/utils/pddl_load.h
    ${DAEX_SRC_DIR}/utils/pddl_load.cpp
    ${DAEX_SRC_DIR}/core/decomposition.h
    ${DAEX_SRC_DIR}/core/goal.h
    ${DAEX_SRC_DIR}/core/strategies.h
    ${DAEX_SRC_DIR}/initialization/init.h
    ${DAEX_SRC_DIR}/evaluation/cpt-yahsp.h
    ${DAEX_SRC_DIR}/evaluation/yahsp.h
    ${DAEX_SRC_DIR}/variation/addgoal.h
    ${DAEX_SRC_DIR}/variation/delgoal.h
    ${DAEX_SRC_DIR}/variation/delatom.h
    ${DAEX_SRC_DIR}/variation/crossover.h
) 


include_directories(
    ${DAEX_SRC_DIR}/utils		    
    ${DAEX_SRC_DIR}/core
    ${DAEX_SRC_DIR}/pack
    ${DAEX_SRC_DIR}/initialization
    ${DAEX_SRC_DIR}/evaluation
    ${DAEX_SRC_DIR}/variation
    ${DAEX_SRC_DIR}
)


#		   
######################################################################################


######################################################################################
###  Specify where CMake can find the libraries
######################################################################################

add_library(daex STATIC ${DAEX_SRC})

TARGET_LINK_LIBRARIES( daex cpt_yahsp_library eo eoutils )
#TARGET_LINK_LIBRARIES( daex  cpt_yahsp_library-common-dae-omp  cpt_yahsp_library-dae eo eoutils )
#TARGET_LINK_LIBRARIES( daex  cpt_yahsp_library-common-dae-noomp  cpt_yahsp_library-dae-noomp eo eoutils )
 
SET_TARGET_PROPERTIES(daex PROPERTIES LINKER_LANGUAGE CXX)


#SET(DAEXMOEO_LIB_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
#SET(LIBRARY_OUTPUT_PATH ${DAEXMOEO_LIB_OUTPUT_PATH})

INCLUDE(../install.cmake)

ADD_DEFINITIONS(-W -Wall -DDAE )#-DCOST_ADD) 

SET (DAEXMOEO_SRC
     core/planningObjectiveVectorTraits.h
     core/planningObjectiveVectorTraits.cpp
     core/planningObjectiveVector.h
     core/moeoDaex.h
     core/planning.h
     #core/planning.cpp
     #core/planningEval.h
     core/planningEval.cpp  
) 	 

INCLUDE_DIRECTORIES(${DAEXMOEO_SRC_DIR}
		    ${DAEXMOEO_SRC_DIR}/src
		    ${DAEXMOEO_SRC_DIR}/src/core
		    ${DAEXMOEO_SRC_DIR}/src/do
		    ${DAEXMOEO_SRC_DIR}/src/utils
		    ${DAEX_SRC_DIR}
		    ${DAEX_SRC_DIR}/core
 		    ${DAEX_SRC_DIR}/utils
		    ${DAEX_SRC_DIR}/pack
	  	    ${DAEX_SRC_DIR}/initialization
    		${DAEX_SRC_DIR}/evaluation
 		    ${DAEX_SRC_DIR}/variation
 		    ${PARADISEO_DIR})
 		    
SET (DAEXMO_SRC
     core/moDaex.h
     core/moplanning.h
     #core/planning.cpp
     #core/planningEval.h
     core/moplanningEval.cpp 
) 	 

INCLUDE_DIRECTORIES(${DAEXMO_SRC_DIR}
		    ${DAEXMOEO_SRC_DIR}/src
		    ${DAEXMOEO_SRC_DIR}/src/core
		    ${DAEXMOEO_SRC_DIR}/src/do
		    ${DAEXMOEO_SRC_DIR}/src/utils
		    ${DAEX_SRC_DIR}
		    ${DAEX_SRC_DIR}/core
 		    ${DAEX_SRC_DIR}/utils
		    ${DAEX_SRC_DIR}/pack
	  	    ${DAEX_SRC_DIR}/initialization
    		${DAEX_SRC_DIR}/evaluation
 		    ${DAEX_SRC_DIR}/variation
 		    ${PARADISEO_DIR})
	    
######################################################################################


######################################################################################
###  Specify where CMake can find the libraries
######################################################################################

# Link with the EO library directory, only if you need it
#LINK_DIRECTORIES(${PARADISEO_DIR}/lib)
#LINK_DIRECTORIES(${DAEX_BIN_DIR} ${DAEXMOEO_BIN_DIR}/lib)


ADD_LIBRARY(daexmoeo STATIC ${DAEXMOEO_SRC})
ADD_LIBRARY(daexmo STATIC ${DAEXMO_SRC})

TARGET_LINK_LIBRARIES(daexmoeo daex moeo eo eoutils )
TARGET_LINK_LIBRARIES(daexmo daex eo eoutils )
 
SET_TARGET_PROPERTIES(daexmoeo PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(daexmo PROPERTIES LINKER_LANGUAGE CXX)
