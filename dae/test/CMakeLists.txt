######################################################################################
### 0) Include headers
######################################################################################

include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${DAEX_SRC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


######################################################################################
### 1) Define test list
######################################################################################

set (TEST_LIST  
        t-atom
		)

######################################################################################
### 3) Create each test
######################################################################################

foreach (test ${TEST_LIST})
	set ("T_${test}_SOURCES" "${test}.cpp")
    add_executable(${test} ${T_${test}_SOURCES})
    target_link_libraries(${test} ${PARADISEO_LIBRARIES} daex cpt_yahsp_library-common cpt_yahsp_library)
    add_test(${test} ${test}) 
endforeach (test)
