# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze

# Include any dependencies generated for this target.
include CMakeFiles/tinyfiledialogs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tinyfiledialogs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tinyfiledialogs.dir/flags.make

CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.o: CMakeFiles/tinyfiledialogs.dir/flags.make
CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.o: lib/tinyfiledialogs/tinyfiledialogs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.o   -c /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/tinyfiledialogs/tinyfiledialogs.c

CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/tinyfiledialogs/tinyfiledialogs.c > CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.i

CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/tinyfiledialogs/tinyfiledialogs.c -o CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.s

# Object files for target tinyfiledialogs
tinyfiledialogs_OBJECTS = \
"CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.o"

# External object files for target tinyfiledialogs
tinyfiledialogs_EXTERNAL_OBJECTS =

lib/libtinyfiledialogs.a: CMakeFiles/tinyfiledialogs.dir/lib/tinyfiledialogs/tinyfiledialogs.c.o
lib/libtinyfiledialogs.a: CMakeFiles/tinyfiledialogs.dir/build.make
lib/libtinyfiledialogs.a: CMakeFiles/tinyfiledialogs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library lib/libtinyfiledialogs.a"
	$(CMAKE_COMMAND) -P CMakeFiles/tinyfiledialogs.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tinyfiledialogs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tinyfiledialogs.dir/build: lib/libtinyfiledialogs.a

.PHONY : CMakeFiles/tinyfiledialogs.dir/build

CMakeFiles/tinyfiledialogs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tinyfiledialogs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tinyfiledialogs.dir/clean

CMakeFiles/tinyfiledialogs.dir/depend:
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles/tinyfiledialogs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tinyfiledialogs.dir/depend
