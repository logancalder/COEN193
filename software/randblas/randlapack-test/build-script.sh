#! /bin/sh

cd build
cmake .. -DRandBLAS_DIR=$RANDBLAS_HOME -DRandLAPACK_DIR=$RANDLAPACK_HOME -Dlapackpp_DIR=$LAPACKPP_HOME
