# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/macbook/tmp/mtm/mtmflix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/macbook/tmp/mtm/mtmflix/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mtmflix.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mtmflix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mtmflix.dir/flags.make

CMakeFiles/mtmflix.dir/newtests/main.c.o: CMakeFiles/mtmflix.dir/flags.make
CMakeFiles/mtmflix.dir/newtests/main.c.o: ../newtests/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macbook/tmp/mtm/mtmflix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mtmflix.dir/newtests/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mtmflix.dir/newtests/main.c.o   -c /Users/macbook/tmp/mtm/mtmflix/newtests/main.c

CMakeFiles/mtmflix.dir/newtests/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mtmflix.dir/newtests/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/macbook/tmp/mtm/mtmflix/newtests/main.c > CMakeFiles/mtmflix.dir/newtests/main.c.i

CMakeFiles/mtmflix.dir/newtests/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mtmflix.dir/newtests/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/macbook/tmp/mtm/mtmflix/newtests/main.c -o CMakeFiles/mtmflix.dir/newtests/main.c.s

CMakeFiles/mtmflix.dir/newtests/main.c.o.requires:

.PHONY : CMakeFiles/mtmflix.dir/newtests/main.c.o.requires

CMakeFiles/mtmflix.dir/newtests/main.c.o.provides: CMakeFiles/mtmflix.dir/newtests/main.c.o.requires
	$(MAKE) -f CMakeFiles/mtmflix.dir/build.make CMakeFiles/mtmflix.dir/newtests/main.c.o.provides.build
.PHONY : CMakeFiles/mtmflix.dir/newtests/main.c.o.provides

CMakeFiles/mtmflix.dir/newtests/main.c.o.provides.build: CMakeFiles/mtmflix.dir/newtests/main.c.o


CMakeFiles/mtmflix.dir/mtmflix.c.o: CMakeFiles/mtmflix.dir/flags.make
CMakeFiles/mtmflix.dir/mtmflix.c.o: ../mtmflix.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macbook/tmp/mtm/mtmflix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mtmflix.dir/mtmflix.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mtmflix.dir/mtmflix.c.o   -c /Users/macbook/tmp/mtm/mtmflix/mtmflix.c

CMakeFiles/mtmflix.dir/mtmflix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mtmflix.dir/mtmflix.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/macbook/tmp/mtm/mtmflix/mtmflix.c > CMakeFiles/mtmflix.dir/mtmflix.c.i

CMakeFiles/mtmflix.dir/mtmflix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mtmflix.dir/mtmflix.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/macbook/tmp/mtm/mtmflix/mtmflix.c -o CMakeFiles/mtmflix.dir/mtmflix.c.s

CMakeFiles/mtmflix.dir/mtmflix.c.o.requires:

.PHONY : CMakeFiles/mtmflix.dir/mtmflix.c.o.requires

CMakeFiles/mtmflix.dir/mtmflix.c.o.provides: CMakeFiles/mtmflix.dir/mtmflix.c.o.requires
	$(MAKE) -f CMakeFiles/mtmflix.dir/build.make CMakeFiles/mtmflix.dir/mtmflix.c.o.provides.build
.PHONY : CMakeFiles/mtmflix.dir/mtmflix.c.o.provides

CMakeFiles/mtmflix.dir/mtmflix.c.o.provides.build: CMakeFiles/mtmflix.dir/mtmflix.c.o


CMakeFiles/mtmflix.dir/series.c.o: CMakeFiles/mtmflix.dir/flags.make
CMakeFiles/mtmflix.dir/series.c.o: ../series.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macbook/tmp/mtm/mtmflix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mtmflix.dir/series.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mtmflix.dir/series.c.o   -c /Users/macbook/tmp/mtm/mtmflix/series.c

CMakeFiles/mtmflix.dir/series.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mtmflix.dir/series.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/macbook/tmp/mtm/mtmflix/series.c > CMakeFiles/mtmflix.dir/series.c.i

CMakeFiles/mtmflix.dir/series.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mtmflix.dir/series.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/macbook/tmp/mtm/mtmflix/series.c -o CMakeFiles/mtmflix.dir/series.c.s

CMakeFiles/mtmflix.dir/series.c.o.requires:

.PHONY : CMakeFiles/mtmflix.dir/series.c.o.requires

CMakeFiles/mtmflix.dir/series.c.o.provides: CMakeFiles/mtmflix.dir/series.c.o.requires
	$(MAKE) -f CMakeFiles/mtmflix.dir/build.make CMakeFiles/mtmflix.dir/series.c.o.provides.build
.PHONY : CMakeFiles/mtmflix.dir/series.c.o.provides

CMakeFiles/mtmflix.dir/series.c.o.provides.build: CMakeFiles/mtmflix.dir/series.c.o


CMakeFiles/mtmflix.dir/user.c.o: CMakeFiles/mtmflix.dir/flags.make
CMakeFiles/mtmflix.dir/user.c.o: ../user.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macbook/tmp/mtm/mtmflix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/mtmflix.dir/user.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mtmflix.dir/user.c.o   -c /Users/macbook/tmp/mtm/mtmflix/user.c

CMakeFiles/mtmflix.dir/user.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mtmflix.dir/user.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/macbook/tmp/mtm/mtmflix/user.c > CMakeFiles/mtmflix.dir/user.c.i

CMakeFiles/mtmflix.dir/user.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mtmflix.dir/user.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/macbook/tmp/mtm/mtmflix/user.c -o CMakeFiles/mtmflix.dir/user.c.s

CMakeFiles/mtmflix.dir/user.c.o.requires:

.PHONY : CMakeFiles/mtmflix.dir/user.c.o.requires

CMakeFiles/mtmflix.dir/user.c.o.provides: CMakeFiles/mtmflix.dir/user.c.o.requires
	$(MAKE) -f CMakeFiles/mtmflix.dir/build.make CMakeFiles/mtmflix.dir/user.c.o.provides.build
.PHONY : CMakeFiles/mtmflix.dir/user.c.o.provides

CMakeFiles/mtmflix.dir/user.c.o.provides.build: CMakeFiles/mtmflix.dir/user.c.o


CMakeFiles/mtmflix.dir/utilities.c.o: CMakeFiles/mtmflix.dir/flags.make
CMakeFiles/mtmflix.dir/utilities.c.o: ../utilities.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macbook/tmp/mtm/mtmflix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/mtmflix.dir/utilities.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mtmflix.dir/utilities.c.o   -c /Users/macbook/tmp/mtm/mtmflix/utilities.c

CMakeFiles/mtmflix.dir/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mtmflix.dir/utilities.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/macbook/tmp/mtm/mtmflix/utilities.c > CMakeFiles/mtmflix.dir/utilities.c.i

CMakeFiles/mtmflix.dir/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mtmflix.dir/utilities.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/macbook/tmp/mtm/mtmflix/utilities.c -o CMakeFiles/mtmflix.dir/utilities.c.s

CMakeFiles/mtmflix.dir/utilities.c.o.requires:

.PHONY : CMakeFiles/mtmflix.dir/utilities.c.o.requires

CMakeFiles/mtmflix.dir/utilities.c.o.provides: CMakeFiles/mtmflix.dir/utilities.c.o.requires
	$(MAKE) -f CMakeFiles/mtmflix.dir/build.make CMakeFiles/mtmflix.dir/utilities.c.o.provides.build
.PHONY : CMakeFiles/mtmflix.dir/utilities.c.o.provides

CMakeFiles/mtmflix.dir/utilities.c.o.provides.build: CMakeFiles/mtmflix.dir/utilities.c.o


# Object files for target mtmflix
mtmflix_OBJECTS = \
"CMakeFiles/mtmflix.dir/newtests/main.c.o" \
"CMakeFiles/mtmflix.dir/mtmflix.c.o" \
"CMakeFiles/mtmflix.dir/series.c.o" \
"CMakeFiles/mtmflix.dir/user.c.o" \
"CMakeFiles/mtmflix.dir/utilities.c.o"

# External object files for target mtmflix
mtmflix_EXTERNAL_OBJECTS =

mtmflix: CMakeFiles/mtmflix.dir/newtests/main.c.o
mtmflix: CMakeFiles/mtmflix.dir/mtmflix.c.o
mtmflix: CMakeFiles/mtmflix.dir/series.c.o
mtmflix: CMakeFiles/mtmflix.dir/user.c.o
mtmflix: CMakeFiles/mtmflix.dir/utilities.c.o
mtmflix: CMakeFiles/mtmflix.dir/build.make
mtmflix: ../maclibs/libmtm_ex3.a
mtmflix: ../maclibs/libmtm.a
mtmflix: CMakeFiles/mtmflix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/macbook/tmp/mtm/mtmflix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable mtmflix"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mtmflix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mtmflix.dir/build: mtmflix

.PHONY : CMakeFiles/mtmflix.dir/build

CMakeFiles/mtmflix.dir/requires: CMakeFiles/mtmflix.dir/newtests/main.c.o.requires
CMakeFiles/mtmflix.dir/requires: CMakeFiles/mtmflix.dir/mtmflix.c.o.requires
CMakeFiles/mtmflix.dir/requires: CMakeFiles/mtmflix.dir/series.c.o.requires
CMakeFiles/mtmflix.dir/requires: CMakeFiles/mtmflix.dir/user.c.o.requires
CMakeFiles/mtmflix.dir/requires: CMakeFiles/mtmflix.dir/utilities.c.o.requires

.PHONY : CMakeFiles/mtmflix.dir/requires

CMakeFiles/mtmflix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mtmflix.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mtmflix.dir/clean

CMakeFiles/mtmflix.dir/depend:
	cd /Users/macbook/tmp/mtm/mtmflix/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/macbook/tmp/mtm/mtmflix /Users/macbook/tmp/mtm/mtmflix /Users/macbook/tmp/mtm/mtmflix/cmake-build-debug /Users/macbook/tmp/mtm/mtmflix/cmake-build-debug /Users/macbook/tmp/mtm/mtmflix/cmake-build-debug/CMakeFiles/mtmflix.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mtmflix.dir/depend

