include(CMakeFindDependencyMacro)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

set(RandBLAS_VERSION "0.1.0-451-g7365c93")
set(RandBLAS_VERSION_MAJOR "0")
set(RandBLAS_VERSION_MINOR "1")
set(RandBLAS_VERSION_PATCH "0")
set(RandBLAS_VERSION_DEVEL "")

# BLAS++
if (NOT blaspp_DIR)
    set(blaspp_DIR /WAVE/users/unix/lcalder/COEN193/software/blaspp/lib64/cmake/blaspp)
endif ()
find_dependency(blaspp)

# Random123
if (NOT Random123_DIR)
    set(Random123_DIR /WAVE/users/unix/lcalder/COEN193/software/random123/include)
endif ()
find_dependency(Random123)

# OpenMP
set(RandBLAS_HAS_OpenMP TRUE)
include(RandBLAS)
