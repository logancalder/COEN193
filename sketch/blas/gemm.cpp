#include <papi.h>
#include <blas.hh>
#include <omp.h>
#include "da.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <sstream> // for std::stringstream

int main(int argc, char* argv[]) {
    // Matrix dimensions and scalars

    // PAPI Setup
    #define NUM_RUNS 10 // The higher the better averaged data

    // PAPI Setup Here
    // ----------------------------------------------------------------------------

    std::vector<std::string> events;
    int numEvents = get_events(events);
    int EventSet[omp_get_max_threads()];
    int numThreads = omp_get_max_threads(); // Default to max threads
    long long values[omp_get_max_threads()];
    long long averageValues[numEvents];
    float averageRuntime = 0;
    float counter = 0;
    std::string sampleName;

    double start_time, end_time;

    // Initialize values of arrays to 0
    for (int i = 0; i < omp_get_max_threads(); i++) {
        values[i] = 0;
    }
    for (int i = 0; i < numEvents; i++) {
        averageValues[i] = 0;
    }

    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        std::cerr << "PAPI initialization failed!" << std::endl;
        return -1;
    }

    const int d = 1000;
    int m, n;

    if (argc == 1) {
        m = 1000; // 1000x1000
        n = 1000;
    } else if (argc == 4) {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
        numThreads = atoi(argv[3]);
        if (n > m) {
            std::cout << "Make sure number of rows are greater than number of cols" << '\n';
            return -1;
        }
    } else {
        std::cout << "Invalid arguments" << '\n';
        return -1;
    }

    const double alpha = 1.0;
    const double beta = 0.0;

    // Leading dimensions
    const int lds = n;
    const int lda = m;
    const int ldb = m;

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Matrix data
    std::vector<double> S_ptr(d * n);
    std::vector<double> A(n * m);
    std::vector<double> B(d * m);

    // Fill matrices with random numbers
    #pragma omp parallel for
    for (int i = 0; i < d * n; ++i) {
        S_ptr[i] = dis(gen);
    }
    #pragma omp parallel for
    for (int i = 0; i < n * m; ++i) {
        A[i] = dis(gen);
    }
    #pragma omp parallel for
    for (int i = 0; i < d * m; ++i) {
        B[i] = dis(gen);
    }

    // BLAS operation parameters
    blas::Layout layout = blas::Layout::RowMajor;
    blas::Op opS = blas::Op::NoTrans;
    blas::Op opA = blas::Op::NoTrans;

    // Perform the matrix multiplication B = alpha * S * A + beta * B
    for (int currentEventNumber = 0; currentEventNumber < numEvents; currentEventNumber++) {
        counter++;

        for (int j = 0; j < NUM_RUNS; j++) { // Loop for PAPI measurements
            initializePAPI(EventSet, events[currentEventNumber]);

            // Dgemm calculations
            start_time = omp_get_wtime();
            startPAPI(EventSet);

            try {
                blas::gemm(layout, opS, opA, d, m, n, alpha, S_ptr.data(), lds, A.data(), lda, beta, B.data(), ldb);
            } catch (const std::exception &e) {
                std::cerr << "BLAS error: " << e.what() << std::endl;
                return -1;
            }

            stopPAPI(values, EventSet, averageValues, currentEventNumber, counter, NUM_RUNS, numEvents);

            end_time = omp_get_wtime();
            averageRuntime += (end_time - start_time);
        }
    }

    // Output a small portion of the result
    std::cout << "Resulting matrix B (first 5x5 block):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << B[i * ldb + j] << " ";
        }
        std::cout << std::endl;
    }

    std::stringstream ss;
    ss << m << "x" << n << "_" << numThreads << "_" << "blas";
    sampleName = ss.str();

    cleanUpPAPI(EventSet, averageValues, averageRuntime, numEvents, events, NUM_RUNS, sampleName);

    return 0;
}
