cmake_minimum_required( VERSION 3.15 )

set( blaspp_use_openmp "true" )
set( blaspp_use_cuda   "false" )
set( blaspp_use_hip    "false" )
set( blaspp_use_sycl   "false" )

include( CMakeFindDependencyMacro )
if (blaspp_use_openmp)
    find_dependency( OpenMP )
endif()

if (blaspp_use_cuda)
    find_dependency( CUDAToolkit )
endif()

if (blaspp_use_hip)
    find_dependency( rocblas )
endif()

# Export private variables used in LAPACK++.
set( blaspp_defines         "-DBLAS_FORTRAN_ADD_;-DBLAS_HAVE_OPENBLAS;-DBLAS_HAVE_CBLAS" )
set( blaspp_libraries       "/WAVE/projects/ycho_lab/software/OpenBLAS-GCC_12.3.0/lib/libopenblas.so;OpenMP::OpenMP_CXX" )

set( blaspp_cblas_found     "true" )
set( blaspp_cblas_include   "" )
set( blaspp_cblas_libraries "" )

include( "${CMAKE_CURRENT_LIST_DIR}/blasppTargets.cmake" )
