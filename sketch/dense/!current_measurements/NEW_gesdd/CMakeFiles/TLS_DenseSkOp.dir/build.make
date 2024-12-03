# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/NEW_gesdd

# Include any dependencies generated for this target.
include CMakeFiles/TLS_DenseSkOp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TLS_DenseSkOp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TLS_DenseSkOp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TLS_DenseSkOp.dir/flags.make

CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o: CMakeFiles/TLS_DenseSkOp.dir/flags.make
CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o: /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/TLS_DenseSkOp.cpp
CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o: CMakeFiles/TLS_DenseSkOp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/NEW_gesdd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o"
	/WAVE/apps/el8/eb/software/GCCcore/12.3.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o -MF CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o.d -o CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o -c /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/TLS_DenseSkOp.cpp

CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.i"
	/WAVE/apps/el8/eb/software/GCCcore/12.3.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/TLS_DenseSkOp.cpp > CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.i

CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.s"
	/WAVE/apps/el8/eb/software/GCCcore/12.3.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/TLS_DenseSkOp.cpp -o CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.s

# Object files for target TLS_DenseSkOp
TLS_DenseSkOp_OBJECTS = \
"CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o"

# External object files for target TLS_DenseSkOp
TLS_DenseSkOp_EXTERNAL_OBJECTS =

TLS_DenseSkOp: CMakeFiles/TLS_DenseSkOp.dir/TLS_DenseSkOp.cpp.o
TLS_DenseSkOp: CMakeFiles/TLS_DenseSkOp.dir/build.make
TLS_DenseSkOp: /WAVE/users/unix/lcalder/ycho_lab/software/RandBLAS/lapackpp-build/lib64/liblapackpp.so
TLS_DenseSkOp: /WAVE/users/unix/lcalder/ycho_lab/software/RandBLAS/blaspp-install/lib64/libblaspp.so
TLS_DenseSkOp: /WAVE/apps2/el8/eb/software/GCCcore/12.3.0/lib64/libgomp.so
TLS_DenseSkOp: /lib64/libpthread.so
TLS_DenseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcudart.so
TLS_DenseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcusolver.so
TLS_DenseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcublas.so
TLS_DenseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libculibos.a
TLS_DenseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcublasLt.so
TLS_DenseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcusparse.so
TLS_DenseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libnvJitLink.so
TLS_DenseSkOp: CMakeFiles/TLS_DenseSkOp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/NEW_gesdd/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TLS_DenseSkOp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TLS_DenseSkOp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TLS_DenseSkOp.dir/build: TLS_DenseSkOp
.PHONY : CMakeFiles/TLS_DenseSkOp.dir/build

CMakeFiles/TLS_DenseSkOp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TLS_DenseSkOp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TLS_DenseSkOp.dir/clean

CMakeFiles/TLS_DenseSkOp.dir/depend:
	cd /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/NEW_gesdd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/NEW_gesdd /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/NEW_gesdd /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/dense/NEW_gesdd/CMakeFiles/TLS_DenseSkOp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TLS_DenseSkOp.dir/depend

