CC=g++
CFLAGS=-I/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/include \
       -I/WAVE/projects/ycho_lab/software/RandBLAS/blaspp-install/include \
       -I/WAVE/projects/ycho_lab/software/RandBLAS/lapackpp-build/include

LDFLAGS=-L/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/lib \
        -L/WAVE/projects/ycho_lab/software/OpenBLAS-GCC_12.3.0/ \
        -L/WAVE/projects/ycho_lab/software/RandBLAS/lapackpp-build/lib64 \
        -L/WAVE/projects/ycho_lab/software/RandBLAS/blaspp-install/lib64

LIBS=-lpapi -lpfm -lpthread -lgomp -fopenmp -lblas -llapack -lblaspp -llapackpp

gemm: gemm.cpp
	$(CC) -o gemm gemm.cpp $(CFLAGS) $(LDFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f gemm
