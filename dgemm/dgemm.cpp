#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <papi.h>
#include <iomanip>
#include <omp.h>
#include "matmul.h"
#include "da.h"

#define LAPACK_INT long int
#ifdef __cplusplus
extern "C"
{
#endif
    void dgemm_(
        const char *TRANSA,
        const char *TRANSB,
        const LAPACK_INT *m,
        const LAPACK_INT *n,
        const LAPACK_INT *k,
        const double *ALPHA,
        double *A,
        const LAPACK_INT *LDA,
        double *B,
        const LAPACK_INT *LDB,
        const double *BETA,
        double *C,
        const LAPACK_INT *LDC);
#ifdef __cplusplus
}
#endif
int main(int argc, char *argv[])
{

#define NUM_TRIALS 4
#define NUM_RUNS 10 // The higher the better averaged data

    std::vector<std::string>
        events;
    int n_events = get_events(events);
    int EventSet = PAPI_NULL;
    EventSet = initializePAPI(EventSet, events);
    long long values[n_events];
    long long averageValues[n_events * NUM_TRIALS];

    double start_time, end_time;

    double *A;
    double *B;
    double *C;
    char transA = 'N';
    char transB = 'N';
    long int m, n, k, lda, ldb, ldc;
    double ALPHA = 2;
    double BETA = 2;

    float counter = 0;
    float total_calculations = NUM_TRIALS * NUM_RUNS;

    // Initialize values of arrays to 0

    for (int i = 0; i < n_events; i++)
    {
        values[i] = 0;
    }
    for (int i = 0; i < n_events * NUM_TRIALS; i++)
    {
        averageValues[i] = 0;
    }

    // Percentage progress bar

    initializeCompletion();

    // Dgemm setup

    m = n = k = 1000;
    lda = m;
    ldb = k;
    ldc = m;

    A = (double *)malloc(sizeof(double) * m * k);
#pragma omp parallel for
    for (int i = 0; i < m * k; i++)
    {
        A[i] = 0;
    }
    B = (double *)malloc(sizeof(double) * k * n);
#pragma omp parallel for
    for (int i = 0; i < k * n; i++)
    {
        B[i] = ((float)rand() / (float)(RAND_MAX));
    }
    C = (double *)malloc(sizeof(double) * m * n);
#pragma omp parallel for
    for (int i = 0; i < m * n; i++)
    {
        C[i] = 0;
    }

    for (int i = 1; i <= NUM_TRIALS; i++)
    {
        // Configure trial parameters here

        std::string numThreads = std::to_string(i);
        setenv("OMP_NUM_THREADS", "4", 1);
        // Loop for measurements that runs NUM_RUNS times
        for (int j = 0; j < NUM_RUNS; j++)
        {
            // Dgemm calculations
            counter++;
            startPAPI(EventSet);
            start_time = omp_get_wtime();
            double *matmulOutput = matmul(A, B, C, ALPHA, BETA, m, n, k);
            end_time = omp_get_wtime();
            stopPAPI(values, EventSet, averageValues, i, n_events, counter, total_calculations);
        }
    }

    cleanUpPAPI(EventSet, averageValues, NUM_TRIALS, n_events, events);

    free(A);
    free(B);
    free(C);

    std::cout << end_time - start_time << std::endl;

    return 0;
}
