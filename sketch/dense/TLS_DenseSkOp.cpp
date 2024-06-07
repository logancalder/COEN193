
#include <blas.hh>
#include <RandBLAS.hh>
#include <lapack.hh>

#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <chrono>

#include <papi.h>
#include "da.h"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

void init_noisy_data(int64_t m, int64_t n, int64_t d, double *AB)
{
    double target_x[n * d];
    double eps[m * d];
    for (int i = 0; i < n; i++)
    {
        target_x[i] = 1; // Target X is the vector of 1's
    }

    RandBLAS::DenseDist Dist_A(m, n);
    RandBLAS::DenseDist Dist_eps(m, d);
    auto state = RandBLAS::RNGState(0);
    auto state1 = RandBLAS::RNGState(1);

    RandBLAS::fill_dense<double>(Dist_A, AB, state);     // Fill A to be a random gaussian
    RandBLAS::fill_dense<double>(Dist_eps, eps, state1); // Fill A to be a random gaussian

    blas::gemm(blas::Layout::ColMajor, blas::Op::NoTrans, blas::Op::NoTrans, m, d, n, 1, AB, m, target_x, n, 0, &AB[m * n], m);

    for (int i = 0; i < m * d; i++)
    {
        AB[m * n + i] += eps[i]; // Add Gaussian Noise to right hand side
    }
}

/* Let A be a tall data matrix of dimensions m by n where m > n and b be a vector of dimension m.
 * In ordinary least squares it assumes that the error lies only in the right hand side vector b,
 * and it aims to find a vector x that minimizes ||A*x - b||_2.
 * On the other hand, total least squares assumes that the input data matrix A could also incur errors.
 * Total least squares aims to find a solution where the error is orthogonal to the regression model.
 */

// To call the executable run ./TLS_DenseSkOp <m> <n> where <m> <n> are the number of rows and columns
// of A respectively. We expect m > 2*n.
int main(int argc, char *argv[])
{
    // PAPI Setup

#define NUM_RUNS 10 // The higher the better averaged data

    // PAPI Setup Here
    // ----------------------------------------------------------------------------

    std::vector<std::string> events;
    int numEvents = get_events(events);
    int EventSet[omp_get_max_threads()];
    int numThreads;
    long long values[omp_get_max_threads()];
    long long averageValues[numEvents];
    float averageRuntime = 0;
    float counter = 0;
    std::string sampleName;

    double start_time, end_time;

    // Initialize values of arrays to 0
    for (int i = 0; i < omp_get_max_threads(); i++)
    {
        values[i] = 0;
    }
    for (int i = 0; i < numEvents; i++)
    {
        averageValues[i] = 0;
    }

    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
    {
        std::cerr << "PAPI initialization failed!" << std::endl;
    }

    // ----------------------------------------------------------------------------

    // Initialize dimensions
    int64_t m; // Number of rows of A, B
    int64_t n; // Number of columns of A

    if (argc == 1)
    {
        m = 10000; // 10000x10000 50000x1000 50000x2000
        n = 500;
    }
    else if (argc == 4)
    {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
        numThreads = atoi(argv[3]);
        if (n > m)
        {
            std::cout << "Make sure number of rows are greater than number of cols" << '\n';
            exit(0);
        }
    }
    else
    {
        std::cout << "Invalid arguments" << '\n';
        exit(1);
    }

    int64_t sk_dim = 2 * (n + 1);

    // Initialize workspace
    double *AB = new double[m * (n + 1)]; // Store [A B] in column major format
    double *SAB = new double[sk_dim * (n + 1)];
    double *X = new double[n];
    double *res = new double[n];

    // Initialize workspace for the sketched svd
    double *U = new double[sk_dim * sk_dim];
    double *svals = new double[n + 1];
    double *VT = new double[(n + 1) * (n + 1)];

    // Initialize noisy gaussian data
    init_noisy_data(m, n, 1, AB);

    // Define properties of the sketching operator

    // Initialize seed for random number generation
    uint32_t seed = 0;

    // Define the dense distribution that the sketching operator will sample from
    /* Additional dense distributions: RandBLAS::DenseDistName::Uniform - entries are iid drawn uniform [-1,1]
     *                                 RandBLAS::DenseDistName::BlackBox - entires are user provided through a buffer
     */

    auto time_constructsketch1 = high_resolution_clock::now();
    RandBLAS::DenseDistName dn = RandBLAS::DenseDistName::Gaussian;

    // Initialize dense distribution struct for the sketching operator


    // 1. PAPI measurements for the sketching operator
    // ----------------------------------------------------------------------------


    for (int currentEventNumber = 0; currentEventNumber < numEvents; currentEventNumber++)
    {
        counter++;

        for (int j = 0; j < NUM_RUNS; j++) // Loop for PAPI measurements
        {
            RandBLAS::DenseDist Dist(sk_dim, // Number of rows of the sketching operator
                                     m,      // Number of columns of the sketching operator
                                     dn);    // Distribution of the entires

            // Construct the dense sketching operator
            RandBLAS::DenseSkOp<double> S(Dist, seed);
            
            initializePAPI(EventSet, events[currentEventNumber]);

            // Dgemm calculations
            start_time = omp_get_wtime();
            startPAPI(EventSet);

            RandBLAS::fill_dense(S);

            stopPAPI(values, EventSet, averageValues, currentEventNumber, counter, NUM_RUNS, numEvents);

            end_time = omp_get_wtime();
            averageRuntime += (end_time - start_time);
        }
    }

    std::stringstream ss;
    ss << m << "x" << n << "_" << numThreads << "_" << "Dense_Fill";
    sampleName = ss.str();

    cleanUpPAPI(EventSet, averageValues, averageRuntime, numEvents, events, NUM_RUNS, sampleName);

    std::cout << "Matrix dimensions: " << m << " by " << n + 1 << '\n';

    // ----------------------------------------------------------------------------

    delete[] AB;
    delete[] SAB;
    delete[] X;
    delete[] res;
    delete[] U;
    delete[] svals;
    delete[] VT;
    return 0;
}
