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
include lib/glfw/examples/CMakeFiles/wave.dir/depend.make

# Include the progress variables for this target.
include lib/glfw/examples/CMakeFiles/wave.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw/examples/CMakeFiles/wave.dir/flags.make

lib/glfw/examples/CMakeFiles/wave.dir/wave.c.o: lib/glfw/examples/CMakeFiles/wave.dir/flags.make
lib/glfw/examples/CMakeFiles/wave.dir/wave.c.o: lib/glfw/examples/wave.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/glfw/examples/CMakeFiles/wave.dir/wave.c.o"
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wave.dir/wave.c.o   -c /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples/wave.c

lib/glfw/examples/CMakeFiles/wave.dir/wave.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wave.dir/wave.c.i"
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples/wave.c > CMakeFiles/wave.dir/wave.c.i

lib/glfw/examples/CMakeFiles/wave.dir/wave.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wave.dir/wave.c.s"
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples/wave.c -o CMakeFiles/wave.dir/wave.c.s

lib/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o: lib/glfw/examples/CMakeFiles/wave.dir/flags.make
lib/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o: lib/glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o"
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wave.dir/__/deps/glad.c.o   -c /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/deps/glad.c

lib/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wave.dir/__/deps/glad.c.i"
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/deps/glad.c > CMakeFiles/wave.dir/__/deps/glad.c.i

lib/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wave.dir/__/deps/glad.c.s"
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/deps/glad.c -o CMakeFiles/wave.dir/__/deps/glad.c.s

# Object files for target wave
wave_OBJECTS = \
"CMakeFiles/wave.dir/wave.c.o" \
"CMakeFiles/wave.dir/__/deps/glad.c.o"

# External object files for target wave
wave_EXTERNAL_OBJECTS =

bin/wave: lib/glfw/examples/CMakeFiles/wave.dir/wave.c.o
bin/wave: lib/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o
bin/wave: lib/glfw/examples/CMakeFiles/wave.dir/build.make
bin/wave: lib/libglfw3.a
bin/wave: /usr/lib/x86_64-linux-gnu/librt.so
bin/wave: /usr/lib/x86_64-linux-gnu/libm.so
bin/wave: /usr/lib/x86_64-linux-gnu/libX11.so
bin/wave: /usr/lib/x86_64-linux-gnu/libXrandr.so
bin/wave: /usr/lib/x86_64-linux-gnu/libXinerama.so
bin/wave: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
bin/wave: /usr/lib/x86_64-linux-gnu/libXcursor.so
bin/wave: lib/glfw/examples/CMakeFiles/wave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ../../../bin/wave"
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw/examples/CMakeFiles/wave.dir/build: bin/wave

.PHONY : lib/glfw/examples/CMakeFiles/wave.dir/build

lib/glfw/examples/CMakeFiles/wave.dir/clean:
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/wave.dir/cmake_clean.cmake
.PHONY : lib/glfw/examples/CMakeFiles/wave.dir/clean

lib/glfw/examples/CMakeFiles/wave.dir/depend:
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/glfw/examples/CMakeFiles/wave.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw/examples/CMakeFiles/wave.dir/depend

