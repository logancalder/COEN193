OpenBLAS_PATH=/WAVE/projects/ycho_lab/software/OpenBLAS-GCC_12.3.0
module load Python
module load OpenMPI/4.1.5
export LD_LIBRARY_PATH=${OpenBLAS_PATH}:${LD_LIBRARY_PATH}
