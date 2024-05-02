This directory is related to dgemm (matrix multiplication using OpenBLAS library).

Files in the main directory are designated to be simulated on a CPU Node (more information on how to run below), and data is recorded using PAPI. To compile the script, the Makefile will include all libraries and merge all scripts needed for the executable to be compiled.

To compile & run:

$ source run_env.sh
$ make
$ ./dgemm

To start a CPU node:
	$ srun --partition=cmp --nodes 1 --ntasks 1 --cpus-per-task 4 --mem=32G --time 0-48:00:00 --pty /bin/bash
This will start a node with 4 CPUs and 32G RAM total >> 32/4 = 8GB RAM/CPU.
The node will be open for 48 hours before it is killed.
