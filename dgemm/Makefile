CC=g++
CFLAGS=-I/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/include
LDFLAGS=-L/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/lib
LIBS=-lpapi -lpfm -lpthread -lgomp -fopenmp -blaspp

loop: dgemm.cpp
	$(CC) -o dgemm dgemm.cpp $(CFLAGS) $(LDFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f loop

