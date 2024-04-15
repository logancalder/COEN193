cmake_minimum_required(VERSION 3.10)

project(TestRandLAPACK)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Checking for RandBLAS ... ")
find_package(RandBLAS REQUIRED)
message(STATUS "Done checking for RandBLAS. ...")

message(STATUS "Looking for BLAS++ ... ")
find_package(blaspp REQUIRED)
message(STATUS "Done looking for BLAS++.")


message(STATUS "Looking for LAPACK++ ... ")
find_package(lapackpp REQUIRED)
message(STATUS "Done looking for LAPACK++.")

message(STATUS "Looking for RandLAPACK ... ")
find_package(RandLAPACK REQUIRED)
message(STATUS "Done looking for RandLAPACK.")

add_executable(
    Main main.cpp
)
target_include_directories(
    Main PUBLIC ${Random123_DIR}
)

target_link_libraries(
    Main PUBLIC RandLAPACK RandBLAS blaspp lapackpp
)
