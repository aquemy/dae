# include the sources

#INCLUDE_DIRECTORIES(${EO_SRC_DIR}/src)
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# target the dae lib


# flags to use with compiler
# VV : -DDAE pour les headers de YAHSP
add_definitions(-W -Wall -DDAE) 


set(DAEX_SRC
    ${DAEX_SRC_DIR}/utils/posix_timer.cpp
    ${DAEX_SRC_DIR}/utils/pddl_load.h
    ${DAEX_SRC_DIR}/utils/pddl_load.cpp
    #utils/evalBestPlanDump.cpp
    ${DAEX_SRC_DIR}/core/decomposition.cpp
    ${DAEX_SRC_DIR}/core/goal.cpp
    ${DAEX_SRC_DIR}/initialization/init.h
    ${DAEX_SRC_DIR}/evaluation/cpt-yahsp.h # evaluation/cpt-yahsp.cpp
    ${DAEX_SRC_DIR}/evaluation/yahsp.h  #evaluation/yahsp.cpp
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

