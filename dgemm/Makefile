CC=g++
CFLAGS=-I/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/include
LDFLAGS=-L/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/software/papi-install/lib
LIBS=-lpapi -lpfm -lpthread -lgomp -fopenmp

loop: papi.cpp
	$(CC) -o dgemm papi.cpp $(CFLAGS) $(LDFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f loop

