
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
add_subdirectory(src)

if(ENABLE_CMAKE_TESTING)
    add_subdirectory(test)
endif(ENABLE_CMAKE_TESTING)

# Link with the EO library directory, only if you need it
link_directories(${PARADISEO_ROOT}/build/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)

# flags to use with compiler
# VV : -DDAE pour les headers de YAHSP
add_definitions(-W -Wall -DDAE)#-DCOST_ADD) 

if(CMAKE_BUILD_TYPE MATCHES Debug)
  #ADD_DEFINITIONS(-DPAPERVERSION)
    message("Building DAE in DEBUG mode !")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    add_definitions(-pg -g)
    message("Flags Debug : ${CMAKE_CXX_FLAGS_DEBUG}")
else()
    message("Building DAE in RELEASE mode !")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    add_definitions(-O3 -DNDEBUG)
    message("Flags Release : ${CMAKE_CXX_FLAGS_RELEASE}")
endif()


IF( DAE_WITH_OMP )
    FIND_PACKAGE(OpenMP REQUIRED)
    IF(OPENMP_FOUND)
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    ENDIF()
ENDIF()


# Mpi Addons
IF(DAE_WITH_MPI)
    MESSAGE("[DAE] Compilation with MPI.")

    #SET(CMAKE_CXX_COMPILER "${MPI_DIR}/bin/mpicxx")
    SET(CMAKE_CXX_COMPILER "/usr/bin/mpicxx")

    # headers location
    INCLUDE_DIRECTORIES(${MPI_DIR}/include)

    # lib location
    LINK_DIRECTORIES(${MPI_DIR}/lib)
ENDIF()

 
# target + link libraries

#ADD_EXECUTABLE(dae test3.cpp)
#ADD_DEPENDENCIES(dae daex  daexmo moeo)
#target_link_libraries(dae ${PARADISEO_LIBRARIES} daex cpt_yahsp_library-common cpt_yahsp_library  daex daexmo )

#LINK_LIBRARIES(daex  daexmoeo eoutils gmp rt ncurses eo gcov gdsl)

#ADD_EXECUTABLE(daeaggreg aggregation.cpp) 
#ADD_DEPENDENCIES(daeaggreg daex daexmoeo moeo)
#TARGET_LINK_LIBRARIES(daeaggreg ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library  daex daexmoeo)

#ADD_EXECUTABLE(daemoeo daemoeo.cpp) 
#ADD_DEPENDENCIES(daemoeo daex daexmoeo moeo)
#TARGET_LINK_LIBRARIES(daemoeo ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library  daex daexmoeo )

add_executable(daeibea daeibea.cpp) 
add_dependencies(daeibea daex moeo)
IF(CPT_WITH_OMP)
    target_link_libraries(daeibea ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common-dae-omp cpt_yahsp_library-dae daex daexmoeo)
ELSE()
    target_link_libraries(daeibea ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library daex daexmoeo)
ENDIF()

IF(WITH_OMP)
    ADD_EXECUTABLE(daeibea-sm daeibea.cpp)
    ADD_DEPENDENCIES(daeibea-sm daex moeo)
    TARGET_LINK_LIBRARIES(daeibea-sm ${PARADISEO_LIBRARIES} cpt_yahsp_library-common-dae-omp cpt_yahsp_library-dae-sm daex daexmoeo)

    ADD_EXECUTABLE(daeibea-mt daeibea.cpp)
    ADD_DEPENDENCIES(daeibea-mt daex-yahsp-mt moeo)
    TARGET_LINK_LIBRARIES(daeibea-mt ${PARADISEO_LIBRARIES} daex-yahsp-mt cpt_yahsp_library-dae-mt daex daexmoeo)
    SET_TARGET_PROPERTIES(
        daeibea-mt
        PROPERTIES
        COMPILE_DEFINITIONS "YAHSP_MT;WITH_OMP"
    )
endif()


#ADD_EXECUTABLE(daensgaII daensgaII.cpp) 
#ADD_DEPENDENCIES(daensgaII daex daexmoeo moeo)
#TARGET_LINK_LIBRARIES(daensgaII ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library  daex daexmoeo )

#ADD_EXECUTABLE(daespeaII daespeaII.cpp) 
#ADD_DEPENDENCIES(daespeaII daex daexmoeo moeo)
#TARGET_LINK_LIBRARIES(daespeaII ${PARADISEO_LIBRARIES} gmp gcov gdsl cpt_yahsp_library-common cpt_yahsp_library daex daexmoeo )
