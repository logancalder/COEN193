export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/OpenBLAS-GCC_12.3.0/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/RandBLAS/lapackpp-build/lib64/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/projects/ycho_lab/software/RandBLAS/blaspp-install/lib64/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/lib/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/WAVE/apps/el8/eb/software/GCCcore/12.3.0/lib64/:$LD_LIBRARY_PATH

module load Python
module load OpenMPI/4.1.5
module load GCC/12.3.0
module load CUDA/12.1.1

total_steps=$((4 * 11))  # Total number of iterations: 2 (m values) * 3 (n values) * 8 (threads values)
step=0
m=50000
n=1000
proc_bind_options=("false" "master" "close" "spread" "true")

for proc_bind in "${proc_bind_options[@]}"; do
    echo "Running with OMP_PROC_BIND=$proc_bind"
    export OMP_PROC_BIND=$proc_bind
        for threads in 4 16 24 48; do
            export OMP_NUM_THREADS=${threads}
            echo $OMP_NUM_THREADS
            ./TLS_SparseSkOp ${m} ${n} ${threads}
            
            step=$((step + 1))
            progress=$((step * 100 / total_steps))
            printf "\rProgress: %d%% (%d/%d)" "${progress}" "${step}" "${total_steps}"
        done
done

echo -e "\nDone."
