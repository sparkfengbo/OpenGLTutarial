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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/fengbo/CLionProjects/OpenGLTutarial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug

# Include any dependencies generated for this target.
include external/glfw/tests/CMakeFiles/reopen.dir/depend.make

# Include the progress variables for this target.
include external/glfw/tests/CMakeFiles/reopen.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw/tests/CMakeFiles/reopen.dir/flags.make

external/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o: external/glfw/tests/CMakeFiles/reopen.dir/flags.make
external/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o: ../external/glfw/tests/reopen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o"
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/reopen.dir/reopen.c.o   -c /Users/fengbo/CLionProjects/OpenGLTutarial/external/glfw/tests/reopen.c

external/glfw/tests/CMakeFiles/reopen.dir/reopen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/reopen.c.i"
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/fengbo/CLionProjects/OpenGLTutarial/external/glfw/tests/reopen.c > CMakeFiles/reopen.dir/reopen.c.i

external/glfw/tests/CMakeFiles/reopen.dir/reopen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/reopen.c.s"
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/fengbo/CLionProjects/OpenGLTutarial/external/glfw/tests/reopen.c -o CMakeFiles/reopen.dir/reopen.c.s

external/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o: external/glfw/tests/CMakeFiles/reopen.dir/flags.make
external/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o: ../external/glfw/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o"
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/reopen.dir/__/deps/glad_gl.c.o   -c /Users/fengbo/CLionProjects/OpenGLTutarial/external/glfw/deps/glad_gl.c

external/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/__/deps/glad_gl.c.i"
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/fengbo/CLionProjects/OpenGLTutarial/external/glfw/deps/glad_gl.c > CMakeFiles/reopen.dir/__/deps/glad_gl.c.i

external/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/__/deps/glad_gl.c.s"
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/fengbo/CLionProjects/OpenGLTutarial/external/glfw/deps/glad_gl.c -o CMakeFiles/reopen.dir/__/deps/glad_gl.c.s

# Object files for target reopen
reopen_OBJECTS = \
"CMakeFiles/reopen.dir/reopen.c.o" \
"CMakeFiles/reopen.dir/__/deps/glad_gl.c.o"

# External object files for target reopen
reopen_EXTERNAL_OBJECTS =

external/glfw/tests/reopen: external/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o
external/glfw/tests/reopen: external/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad_gl.c.o
external/glfw/tests/reopen: external/glfw/tests/CMakeFiles/reopen.dir/build.make
external/glfw/tests/reopen: external/glfw/src/libglfw3.a
external/glfw/tests/reopen: external/glfw/tests/CMakeFiles/reopen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable reopen"
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reopen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw/tests/CMakeFiles/reopen.dir/build: external/glfw/tests/reopen

.PHONY : external/glfw/tests/CMakeFiles/reopen.dir/build

external/glfw/tests/CMakeFiles/reopen.dir/clean:
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/reopen.dir/cmake_clean.cmake
.PHONY : external/glfw/tests/CMakeFiles/reopen.dir/clean

external/glfw/tests/CMakeFiles/reopen.dir/depend:
	cd /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fengbo/CLionProjects/OpenGLTutarial /Users/fengbo/CLionProjects/OpenGLTutarial/external/glfw/tests /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests /Users/fengbo/CLionProjects/OpenGLTutarial/cmake-build-debug/external/glfw/tests/CMakeFiles/reopen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw/tests/CMakeFiles/reopen.dir/depend

