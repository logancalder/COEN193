# TLS Dense Sketching
## Introduction
This directory is related to TLS Dense Sketching, and conducts performance analysis on three regions of the sketch: Distribution, Sketch, and SVD.

Files in the main directory are designated to be simulated on a CPU Node (more information on how to run below), and data is recorded using PAPI. If a compile is needed, load the respective region designated to be simulated onto TLS_DenseSkOp and navigate to a blank child directory. Compilation requires using cmake for RandBLAS.

## Compilation & Setup

To compile:
```bash
$ source lib.sh
$ cmake .. -DRandBLAS_DIR=/WAVE/users/unix/lcalder/ycho_lab/software/RandBLAS/RandBLAS-install/lib64/cmake/ -Dlapackpp_DIR=/WAVE/users/unix/lcalder/ycho_lab/software/RandBLAS/lapackpp-build/lib64/cmake/lapackpp/ -Dblaspp_DIR=/WAVE/users/unix/lcalder/ycho_lab/software/RandBLAS/blaspp-install/lib64/cmake/blaspp -DRandom123_DIR=/WAVE/users/unix/lcalder/ycho_lab/software/RandBLAS/random123/include/
$ make -j install
```

To run on a CPU node (PAPI will not work on login node):
```bash
$ source run.sh
```

To start a CPU node:
```bash
$ srun --partition=cmp --nodes 1 --ntasks 1 --cpus-per-task 4 --mem=32G --time 0-48:00:00 --pty /bin/bash
```

This will start a node with 4 CPUs and 32G RAM total >> 32/4 = 8GB RAM/CPU.
The node will be open for 48 hours before it is killed.

## Tmux

Running on Tmux is highly advisable as sketching may take a long time to compute, and multiple trials are run to obtain averages. Use the following to use Tmux:

To open a new Tmux session:
```bash
$ tmux
```

To exit out of a Tmux session:
```bash
$ ctrlb + d
```

To see running sessions:
```bash
$ tmux ls
```

To reconnect to a Tmux session, where # is the ID of session
```bash
$ tmux attach -t #
```

To kill a session, where # is the ID of session:
```bash
$ tmux kill-session -t #
```



