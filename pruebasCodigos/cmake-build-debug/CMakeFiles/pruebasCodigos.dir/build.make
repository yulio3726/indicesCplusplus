# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.1.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.1.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\julio\ClionProjects\pruebasCodigos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\julio\ClionProjects\pruebasCodigos\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pruebasCodigos.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pruebasCodigos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pruebasCodigos.dir/flags.make

CMakeFiles/pruebasCodigos.dir/main.cpp.obj: CMakeFiles/pruebasCodigos.dir/flags.make
CMakeFiles/pruebasCodigos.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\julio\ClionProjects\pruebasCodigos\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pruebasCodigos.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\pruebasCodigos.dir\main.cpp.obj -c C:\Users\julio\ClionProjects\pruebasCodigos\main.cpp

CMakeFiles/pruebasCodigos.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pruebasCodigos.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\julio\ClionProjects\pruebasCodigos\main.cpp > CMakeFiles\pruebasCodigos.dir\main.cpp.i

CMakeFiles/pruebasCodigos.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pruebasCodigos.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\julio\ClionProjects\pruebasCodigos\main.cpp -o CMakeFiles\pruebasCodigos.dir\main.cpp.s

CMakeFiles/pruebasCodigos.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/pruebasCodigos.dir/main.cpp.obj.requires

CMakeFiles/pruebasCodigos.dir/main.cpp.obj.provides: CMakeFiles/pruebasCodigos.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\pruebasCodigos.dir\build.make CMakeFiles/pruebasCodigos.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/pruebasCodigos.dir/main.cpp.obj.provides

CMakeFiles/pruebasCodigos.dir/main.cpp.obj.provides.build: CMakeFiles/pruebasCodigos.dir/main.cpp.obj


# Object files for target pruebasCodigos
pruebasCodigos_OBJECTS = \
"CMakeFiles/pruebasCodigos.dir/main.cpp.obj"

# External object files for target pruebasCodigos
pruebasCodigos_EXTERNAL_OBJECTS =

pruebasCodigos.exe: CMakeFiles/pruebasCodigos.dir/main.cpp.obj
pruebasCodigos.exe: CMakeFiles/pruebasCodigos.dir/build.make
pruebasCodigos.exe: CMakeFiles/pruebasCodigos.dir/linklibs.rsp
pruebasCodigos.exe: CMakeFiles/pruebasCodigos.dir/objects1.rsp
pruebasCodigos.exe: CMakeFiles/pruebasCodigos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\julio\ClionProjects\pruebasCodigos\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pruebasCodigos.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pruebasCodigos.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pruebasCodigos.dir/build: pruebasCodigos.exe

.PHONY : CMakeFiles/pruebasCodigos.dir/build

CMakeFiles/pruebasCodigos.dir/requires: CMakeFiles/pruebasCodigos.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/pruebasCodigos.dir/requires

CMakeFiles/pruebasCodigos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\pruebasCodigos.dir\cmake_clean.cmake
.PHONY : CMakeFiles/pruebasCodigos.dir/clean

CMakeFiles/pruebasCodigos.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\julio\ClionProjects\pruebasCodigos C:\Users\julio\ClionProjects\pruebasCodigos C:\Users\julio\ClionProjects\pruebasCodigos\cmake-build-debug C:\Users\julio\ClionProjects\pruebasCodigos\cmake-build-debug C:\Users\julio\ClionProjects\pruebasCodigos\cmake-build-debug\CMakeFiles\pruebasCodigos.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pruebasCodigos.dir/depend

