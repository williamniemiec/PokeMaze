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
include CMakeFiles/obj_loader.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/obj_loader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/obj_loader.dir/flags.make

CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.o: CMakeFiles/obj_loader.dir/flags.make
CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.o: lib/obj_loader/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.o   -c /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/glad.c

CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/glad.c > CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.i

CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/glad.c -o CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.s

CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.o: CMakeFiles/obj_loader.dir/flags.make
CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.o: lib/obj_loader/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.o -c /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/stb_image.cpp

CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/stb_image.cpp > CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.i

CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/stb_image.cpp -o CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.s

CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.o: CMakeFiles/obj_loader.dir/flags.make
CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.o: lib/obj_loader/tiny_obj_loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.o -c /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/tiny_obj_loader.cpp

CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/tiny_obj_loader.cpp > CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.i

CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/lib/obj_loader/tiny_obj_loader.cpp -o CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.s

# Object files for target obj_loader
obj_loader_OBJECTS = \
"CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.o" \
"CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.o" \
"CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.o"

# External object files for target obj_loader
obj_loader_EXTERNAL_OBJECTS =

lib/libobj_loader.a: CMakeFiles/obj_loader.dir/lib/obj_loader/glad.c.o
lib/libobj_loader.a: CMakeFiles/obj_loader.dir/lib/obj_loader/stb_image.cpp.o
lib/libobj_loader.a: CMakeFiles/obj_loader.dir/lib/obj_loader/tiny_obj_loader.cpp.o
lib/libobj_loader.a: CMakeFiles/obj_loader.dir/build.make
lib/libobj_loader.a: CMakeFiles/obj_loader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library lib/libobj_loader.a"
	$(CMAKE_COMMAND) -P CMakeFiles/obj_loader.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/obj_loader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/obj_loader.dir/build: lib/libobj_loader.a

.PHONY : CMakeFiles/obj_loader.dir/build

CMakeFiles/obj_loader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/obj_loader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/obj_loader.dir/clean

CMakeFiles/obj_loader.dir/depend:
	cd /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze /home/williamniemiec/Documents/workspace/ufrgs/PokeMaze/CMakeFiles/obj_loader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/obj_loader.dir/depend

