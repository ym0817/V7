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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/build

# Include any dependencies generated for this target.
include CMakeFiles/yolov8_snpe210.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/yolov8_snpe210.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/yolov8_snpe210.dir/flags.make

CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o: CMakeFiles/yolov8_snpe210.dir/flags.make
CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o: ../src/yolo_tiny_640x640_85classes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o -c /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/src/yolo_tiny_640x640_85classes.cpp

CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/src/yolo_tiny_640x640_85classes.cpp > CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.i

CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/src/yolo_tiny_640x640_85classes.cpp -o CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.s

CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o.requires:

.PHONY : CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o.requires

CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o.provides: CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o.requires
	$(MAKE) -f CMakeFiles/yolov8_snpe210.dir/build.make CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o.provides.build
.PHONY : CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o.provides

CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o.provides.build: CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o


# Object files for target yolov8_snpe210
yolov8_snpe210_OBJECTS = \
"CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o"

# External object files for target yolov8_snpe210
yolov8_snpe210_EXTERNAL_OBJECTS =

yolov8_snpe210: CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o
yolov8_snpe210: CMakeFiles/yolov8_snpe210.dir/build.make
yolov8_snpe210: CMakeFiles/yolov8_snpe210.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable yolov8_snpe210"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yolov8_snpe210.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/yolov8_snpe210.dir/build: yolov8_snpe210

.PHONY : CMakeFiles/yolov8_snpe210.dir/build

CMakeFiles/yolov8_snpe210.dir/requires: CMakeFiles/yolov8_snpe210.dir/src/yolo_tiny_640x640_85classes.cpp.o.requires

.PHONY : CMakeFiles/yolov8_snpe210.dir/requires

CMakeFiles/yolov8_snpe210.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/yolov8_snpe210.dir/cmake_clean.cmake
.PHONY : CMakeFiles/yolov8_snpe210.dir/clean

CMakeFiles/yolov8_snpe210.dir/depend:
	cd /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210 /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210 /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/build /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/build /home/ymm/Workspace/Git/yolov7_on_snpe/yolov7_tiny-snpe210/build/CMakeFiles/yolov8_snpe210.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/yolov8_snpe210.dir/depend

