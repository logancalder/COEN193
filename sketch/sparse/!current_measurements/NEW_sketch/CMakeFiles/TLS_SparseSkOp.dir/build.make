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
CMAKE_SOURCE_DIR = /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/NEW_sketch

# Include any dependencies generated for this target.
include CMakeFiles/TLS_SparseSkOp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TLS_SparseSkOp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TLS_SparseSkOp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TLS_SparseSkOp.dir/flags.make

CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o: CMakeFiles/TLS_SparseSkOp.dir/flags.make
CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o: /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/TLS_SparseSkOp.cpp
CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o: CMakeFiles/TLS_SparseSkOp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/NEW_sketch/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o"
	/WAVE/apps/el8/eb/software/GCCcore/12.3.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o -MF CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o.d -o CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o -c /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/TLS_SparseSkOp.cpp

CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.i"
	/WAVE/apps/el8/eb/software/GCCcore/12.3.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/TLS_SparseSkOp.cpp > CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.i

CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.s"
	/WAVE/apps/el8/eb/software/GCCcore/12.3.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/TLS_SparseSkOp.cpp -o CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.s

# Object files for target TLS_SparseSkOp
TLS_SparseSkOp_OBJECTS = \
"CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o"

# External object files for target TLS_SparseSkOp
TLS_SparseSkOp_EXTERNAL_OBJECTS =

TLS_SparseSkOp: CMakeFiles/TLS_SparseSkOp.dir/TLS_SparseSkOp.cpp.o
TLS_SparseSkOp: CMakeFiles/TLS_SparseSkOp.dir/build.make
TLS_SparseSkOp: /WAVE/users/unix/lcalder/ycho_lab/software/RandBLAS/lapackpp-build/lib64/liblapackpp.so
TLS_SparseSkOp: /WAVE/users/unix/lcalder/ycho_lab/software/RandBLAS/blaspp-install/lib64/libblaspp.so
TLS_SparseSkOp: /WAVE/apps2/el8/eb/software/GCCcore/12.3.0/lib64/libgomp.so
TLS_SparseSkOp: /lib64/libpthread.so
TLS_SparseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcudart.so
TLS_SparseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcusolver.so
TLS_SparseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcublas.so
TLS_SparseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libculibos.a
TLS_SparseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcublasLt.so
TLS_SparseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libcusparse.so
TLS_SparseSkOp: /WAVE/apps/el8/eb/software/CUDA/12.1.1/lib/libnvJitLink.so
TLS_SparseSkOp: CMakeFiles/TLS_SparseSkOp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/NEW_sketch/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TLS_SparseSkOp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TLS_SparseSkOp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TLS_SparseSkOp.dir/build: TLS_SparseSkOp
.PHONY : CMakeFiles/TLS_SparseSkOp.dir/build

CMakeFiles/TLS_SparseSkOp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TLS_SparseSkOp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TLS_SparseSkOp.dir/clean

CMakeFiles/TLS_SparseSkOp.dir/depend:
	cd /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/NEW_sketch && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/NEW_sketch /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/NEW_sketch /WAVE/users2/unix/lcalder/ycho_lab/logan_calder/COEN193/sketch/sparse/NEW_sketch/CMakeFiles/TLS_SparseSkOp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TLS_SparseSkOp.dir/depend

