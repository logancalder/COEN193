include(CMakeFindDependencyMacro)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

set(RandLAPACK_VERSION "0.1.0-120-g59f6284")
set(RandLAPACK_VERSION_MAJOR "0")
set(RandLAPACK_VERSION_MINOR "1")
set(RandLAPACK_VERSION_PATCH "0")
set(RandLAPACK_VERSION_DEVEL "")

# randblas
if (NOT RandBLAS_DIR)
    set(RandBLAS_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()
find_dependency(RandBLAS)

# lapack++
if (NOT lapackpp_DIR)
    set(lapackpp_DIR /WAVE/users/unix/gpunjabi/local/lapackpp/lib64/cmake/lapackpp)
endif()
find_dependency(lapackpp)

include(RandLAPACK)
