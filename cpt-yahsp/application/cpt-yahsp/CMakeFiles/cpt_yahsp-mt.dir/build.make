# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /users/tao/khouadjia/descarwin/trunk/cpt-yahsp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /users/tao/khouadjia/descarwin/trunk/cpt-yahsp

# Include any dependencies generated for this target.
include application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/depend.make

# Include the progress variables for this target.
include application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/progress.make

# Include the compile flags for this target's objects.
include application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/flags.make

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o: application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/flags.make
application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o: application/cpt-yahsp/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o"
	cd /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -fopenmp -o CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o -c /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp/main.cpp

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpt_yahsp-mt.dir/main.cpp.i"
	cd /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -fopenmp -E /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp/main.cpp > CMakeFiles/cpt_yahsp-mt.dir/main.cpp.i

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpt_yahsp-mt.dir/main.cpp.s"
	cd /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -fopenmp -S /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp/main.cpp -o CMakeFiles/cpt_yahsp-mt.dir/main.cpp.s

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.requires:
.PHONY : application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.requires

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.provides: application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.requires
	$(MAKE) -f application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/build.make application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.provides.build
.PHONY : application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.provides

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.provides.build: application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o
.PHONY : application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.provides.build

# Object files for target cpt_yahsp-mt
cpt_yahsp__mt_OBJECTS = \
"CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o"

# External object files for target cpt_yahsp-mt
cpt_yahsp__mt_EXTERNAL_OBJECTS =

cpt_yahsp-mt: application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o
cpt_yahsp-mt: lib/libcpt_yahsp_library-common-omp.a
cpt_yahsp-mt: lib/libcpt_yahsp_library-mt.a
cpt_yahsp-mt: lib/libgdsl.a
cpt_yahsp-mt: application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/build.make
cpt_yahsp-mt: application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../cpt_yahsp-mt"
	cd /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpt_yahsp-mt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/build: cpt_yahsp-mt
.PHONY : application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/build

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/requires: application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/main.cpp.o.requires
.PHONY : application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/requires

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/clean:
	cd /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp && $(CMAKE_COMMAND) -P CMakeFiles/cpt_yahsp-mt.dir/cmake_clean.cmake
.PHONY : application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/clean

application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/depend:
	cd /users/tao/khouadjia/descarwin/trunk/cpt-yahsp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/tao/khouadjia/descarwin/trunk/cpt-yahsp /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp /users/tao/khouadjia/descarwin/trunk/cpt-yahsp /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp /users/tao/khouadjia/descarwin/trunk/cpt-yahsp/application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : application/cpt-yahsp/CMakeFiles/cpt_yahsp-mt.dir/depend

