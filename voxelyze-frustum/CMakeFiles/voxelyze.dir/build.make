# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum

# Include any dependencies generated for this target.
include CMakeFiles/voxelyze.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/voxelyze.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/voxelyze.dir/flags.make

CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o: CMakeFiles/voxelyze.dir/flags.make
CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o: Voxelyze/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o -c /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/main.cpp

CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/main.cpp > CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.i

CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/main.cpp -o CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.s

CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o.requires:
.PHONY : CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o.requires

CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o.provides: CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/voxelyze.dir/build.make CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o.provides.build
.PHONY : CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o.provides

CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o.provides.build: CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o

# Object files for target voxelyze
voxelyze_OBJECTS = \
"CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o"

# External object files for target voxelyze
voxelyze_EXTERNAL_OBJECTS = \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/Utils/XML_Rip.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VXS_Voxel.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VXS_Bond.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VX_Sim.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VX_SimGA.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VX_Object.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VX_MeshUtil.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VX_FRegion.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VX_FEA.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/VX_Environment.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/Utils/Mesh.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/Utils/tinyxml.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/Utils/tinyxmlerror.o" \
"/home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/Voxelyze/Utils/tinyxmlparser.o"

voxelyze: CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o
voxelyze: Voxelyze/Utils/XML_Rip.o
voxelyze: Voxelyze/VXS_Voxel.o
voxelyze: Voxelyze/VXS_Bond.o
voxelyze: Voxelyze/VX_Sim.o
voxelyze: Voxelyze/VX_SimGA.o
voxelyze: Voxelyze/VX_Object.o
voxelyze: Voxelyze/VX_MeshUtil.o
voxelyze: Voxelyze/VX_FRegion.o
voxelyze: Voxelyze/VX_FEA.o
voxelyze: Voxelyze/VX_Environment.o
voxelyze: Voxelyze/Utils/Mesh.o
voxelyze: Voxelyze/Utils/tinyxml.o
voxelyze: Voxelyze/Utils/tinyxmlerror.o
voxelyze: Voxelyze/Utils/tinyxmlparser.o
voxelyze: CMakeFiles/voxelyze.dir/build.make
voxelyze: /usr/local/lib/libopencv_videostab.so.2.4.9
voxelyze: /usr/local/lib/libopencv_video.so.2.4.9
voxelyze: /usr/local/lib/libopencv_ts.a
voxelyze: /usr/local/lib/libopencv_superres.so.2.4.9
voxelyze: /usr/local/lib/libopencv_stitching.so.2.4.9
voxelyze: /usr/local/lib/libopencv_photo.so.2.4.9
voxelyze: /usr/local/lib/libopencv_ocl.so.2.4.9
voxelyze: /usr/local/lib/libopencv_objdetect.so.2.4.9
voxelyze: /usr/local/lib/libopencv_nonfree.so.2.4.9
voxelyze: /usr/local/lib/libopencv_ml.so.2.4.9
voxelyze: /usr/local/lib/libopencv_legacy.so.2.4.9
voxelyze: /usr/local/lib/libopencv_imgproc.so.2.4.9
voxelyze: /usr/local/lib/libopencv_highgui.so.2.4.9
voxelyze: /usr/local/lib/libopencv_gpu.so.2.4.9
voxelyze: /usr/local/lib/libopencv_flann.so.2.4.9
voxelyze: /usr/local/lib/libopencv_features2d.so.2.4.9
voxelyze: /usr/local/lib/libopencv_core.so.2.4.9
voxelyze: /usr/local/lib/libopencv_contrib.so.2.4.9
voxelyze: /usr/local/lib/libopencv_calib3d.so.2.4.9
voxelyze: /usr/lib/x86_64-linux-gnu/libGLU.so
voxelyze: /usr/lib/x86_64-linux-gnu/libGL.so
voxelyze: /usr/lib/x86_64-linux-gnu/libSM.so
voxelyze: /usr/lib/x86_64-linux-gnu/libICE.so
voxelyze: /usr/lib/x86_64-linux-gnu/libX11.so
voxelyze: /usr/lib/x86_64-linux-gnu/libXext.so
voxelyze: /usr/lib/x86_64-linux-gnu/libglut.so
voxelyze: /usr/lib/x86_64-linux-gnu/libXmu.so
voxelyze: /usr/lib/x86_64-linux-gnu/libXi.so
voxelyze: /usr/local/lib/libopencv_nonfree.so.2.4.9
voxelyze: /usr/local/lib/libopencv_ocl.so.2.4.9
voxelyze: /usr/local/lib/libopencv_gpu.so.2.4.9
voxelyze: /usr/local/lib/libopencv_photo.so.2.4.9
voxelyze: /usr/local/lib/libopencv_objdetect.so.2.4.9
voxelyze: /usr/local/lib/libopencv_legacy.so.2.4.9
voxelyze: /usr/local/lib/libopencv_video.so.2.4.9
voxelyze: /usr/local/lib/libopencv_ml.so.2.4.9
voxelyze: /usr/local/lib/libopencv_calib3d.so.2.4.9
voxelyze: /usr/local/lib/libopencv_features2d.so.2.4.9
voxelyze: /usr/local/lib/libopencv_highgui.so.2.4.9
voxelyze: /usr/local/lib/libopencv_imgproc.so.2.4.9
voxelyze: /usr/local/lib/libopencv_flann.so.2.4.9
voxelyze: /usr/local/lib/libopencv_core.so.2.4.9
voxelyze: CMakeFiles/voxelyze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable voxelyze"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/voxelyze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/voxelyze.dir/build: voxelyze
.PHONY : CMakeFiles/voxelyze.dir/build

CMakeFiles/voxelyze.dir/requires: CMakeFiles/voxelyze.dir/Voxelyze/main.cpp.o.requires
.PHONY : CMakeFiles/voxelyze.dir/requires

CMakeFiles/voxelyze.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/voxelyze.dir/cmake_clean.cmake
.PHONY : CMakeFiles/voxelyze.dir/clean

CMakeFiles/voxelyze.dir/depend:
	cd /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum /home/ubuntu/kernel/simulation/voxelyze/voxelyze-frustum/CMakeFiles/voxelyze.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/voxelyze.dir/depend

