#!/bin/bash

# File to run
executable="./TLS_DenseSkOp"
param1=50000
param2=2000

# Thread counts and OMP_PROC_BIND settings
threads=(2 4 8 12 16 20 24 28 32 36 40 44 48)
proc_bind_settings=("false" "master" "close" "spread" "true")

# Directory to store CSV files
output_dir="dense_output_csvs_502"
mkdir -p $output_dir

# Loop through OMP_PROC_BIND settings
for bind_setting in "${proc_bind_settings[@]}"; do
    # Prepare the CSV file for this setting
    csv_file="${output_dir}/runtime_${bind_setting}.csv"
    echo "Threads,create_sketch,sketch,gesdd" > "$csv_file"

    # Loop through thread counts
    for thread_count in "${threads[@]}"; do
        # Initialize variables for averages
        total_dense_sketch=0
        total_sketch_ab=0
        total_gesdd=0

        # Run 10 times and accumulate the times
        for i in {1..10}; do
            # Set environment variables
            export OMP_NUM_THREADS=$thread_count
            export OMP_PROC_BIND=$bind_setting

            # Run the executable and capture output
            output=$($executable $param1 $param2)

            # Extract relevant times
            time_dense_sketch=$(echo "$output" | grep "Time to create dense sketch" | awk -F ':' '{print $2}' | awk '{print $1}')
            time_sketch_ab=$(echo "$output" | grep "Time to sketch AB" | awk -F ':' '{print $2}' | awk '{print $1}')
            time_gesdd=$(echo "$output" | grep "Time to perform TLS on sketched matrix" | awk -F ':' '{print $2}' | awk '{print $1}')

            # Add the times to the totals
            total_dense_sketch=$(echo "$total_dense_sketch + $time_dense_sketch" | bc)
            total_sketch_ab=$(echo "$total_sketch_ab + $time_sketch_ab" | bc)
            total_gesdd=$(echo "$total_gesdd + $time_gesdd" | bc)
        done

        # Calculate the averages
        avg_dense_sketch=$(echo "$total_dense_sketch / 10" | bc -l)
        avg_sketch_ab=$(echo "$total_sketch_ab / 10" | bc -l)
        avg_gesdd=$(echo "$total_gesdd / 10" | bc -l)

        # Write the average results to the CSV file
        echo "$thread_count,$avg_dense_sketch,$avg_sketch_ab,$avg_gesdd" >> "$csv_file"
    done
done
