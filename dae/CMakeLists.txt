

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/src_cpt
  ${CMAKE_CURRENT_SOURCE_DIR}/src_daex
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${DAEX_SRC_DIR}
  ${DAEX_SRC_DIR}/core
  ${DAEX_SRC_DIR}/utils
  ${DAEX_SRC_DIR}/pack
  ${DAEX_SRC_DIR}/initialization
  ${DAEX_SRC_DIR}/evaluation
  ${DAEX_SRC_DIR}/variation	
  ${CPT_YAHSP_SRC_DIR}
  ${GDSL_LIBRARY}   
  )
  
######################################################################################
### 0) Include subdirectories
######################################################################################
#add_subdirectory(doc)
add_subdirectory(src_daex)
add_subdirectory(src)

if(ENABLE_CMAKE_TESTING)
    add_subdirectory(test)
endif(ENABLE_CMAKE_TESTING)

# Link with the EO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_ROOT}/build/lib)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)


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

#OK ADD_EXECUTABLE(dae dae.cpp)
#OKADD_DEPENDENCIES(dae daex)
#OKtarget_link_libraries(dae ${PARADISEO_LIBRARIES} daex cpt_yahsp_library-common cpt_yahsp_library)

#LINK_LIBRARIES(daex  daexmoeo eoutils gmp rt ncurses eo gcov gdsl)

ADD_EXECUTABLE(daemoeo daemoeo.cpp) 
ADD_DEPENDENCIES(daemoeo daex daexmoeo moeo)
TARGET_LINK_LIBRARIES(daemoeo ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library  daex daexmoeo )

ADD_EXECUTABLE(daeibea daeibea.cpp) 
ADD_DEPENDENCIES(daeibea daex daexmoeo moeo)
TARGET_LINK_LIBRARIES(daeibea ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library  daex daexmoeo)

ADD_EXECUTABLE(daensgaII daensgaII.cpp) 
ADD_DEPENDENCIES(daensgaII daex daexmoeo moeo)
TARGET_LINK_LIBRARIES(daensgaII ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library  daex daexmoeo )

ADD_EXECUTABLE(daespeaII daespeaII.cpp) 
ADD_DEPENDENCIES(daespeaII daex daexmoeo moeo)
TARGET_LINK_LIBRARIES(daespeaII ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library daex daexmoeo )
