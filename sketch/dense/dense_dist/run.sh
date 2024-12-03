export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/OpenBLAS-GCC_12.3.0/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/RandBLAS/lapackpp-build/lib64/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/RandBLAS/blaspp-install/lib64/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/lib/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/apps/el8/eb/software/GCCcore/12.3.0/lib64/:$LD_LIBRARY_PATH

module load Python
module load OpenMPI/4.1.5
module load GCC/12.3.0
module load CUDA/12.1.1

total_steps=$((2 * 3 * 4))  # Total number of iterations: 2 (m values) * 3 (n values) * 4 (threads values)
step=0

for m in 50000; do
    for n in 1000 2000; do
        for threads in 1 2 3 4; do
            export OMP_NUM_THREADS=${threads}
            ./TLS_DenseSkOp ${m} ${n} ${threads}
            
            step=$((step + 1))
            progress=$((step * 100 / total_steps))
            printf "\rProgress: %d%% (%d/%d)" "${progress}" "${step}" "${total_steps}"
        done
    done
done

echo -e "\nDone."
