OpenBLAS_PATH=/WAVE/projects/ycho_lab/software/OpenBLAS-GCC_12.3.0
Papi_PATH=/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/lib
GCC_PATH=/WAVE/apps/el8/eb/software/GCCcore/12.3.0/lib64
module load Python
module load OpenMPI/4.1.5
export LD_LIBRARY_PATH=${OpenBLAS_PATH}:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=${Papi_PATH}:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=${GCC_PATH}:${LD_LIBRARY_PATH}
