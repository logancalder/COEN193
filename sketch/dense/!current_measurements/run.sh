export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/OpenBLAS-GCC_12.3.0/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/RandBLAS/lapackpp-build/lib64/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/RandBLAS/blaspp-install/lib64/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/lib/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/apps/el8/eb/software/GCCcore/12.3.0/lib64/:$LD_LIBRARY_PATH

module load Python
module load OpenMPI/4.1.5
module load GCC/12.3.0
module load CUDA/12.1.1

source NEW_create_dense_dist/run.sh
source NEW_gesdd/run.sh
source NEW_sketch/run.sh

echo -e "\nDone."
