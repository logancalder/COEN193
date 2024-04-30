#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <papi.h>
#include <iomanip>
#include "matmul.h"
#include "externals.h"
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
    double *A;
    double *B;
    double *C;
    char transA = 'N';
    char transB = 'N';
    long int m, n, k, lda, ldb, ldc;
    double ALPHA = 2;
    double BETA = 2;

    int EventSet = PAPI_NULL;
    EventSet = initializePAPI(EventSet);

#define NUM_TRIALS 5
#define NUM_RUNS 10 // The higher the better averaged data
    std::string fileName = getCurrentDateTimeString();

    // Setup for PAPI

    long long values[getNumEvents()];
    long long averageValues[getNumEvents() * 10];

    for (int i; i < getNumEvents(); i++)
    {
        values[i] = 0;
    }
    for (int i; i < getNumEvents() * NUM_TRIALS; i++)
    {
        averageValues[i] = 0;
    }

    for (int i = 0; i < NUM_TRIALS; i++)
    {
        std::string numThreads = std::to_string(i);
        m = n = k = 100;
        setenv("OMP_NUM_THREADS", numThreads.c_str(), 1);
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

        // Loop for measurements

        for (int j = 0; j < NUM_RUNS; j++)
        {
            std::cout << "Trial #" << i << " Run #" << j << std::endl;

            startPAPI(EventSet);

            double *matmulOutput = matmul(A, B, C, ALPHA, BETA, m, n, k);

            stopPAPI(values, EventSet, averageValues, i);
        }
    }

    cleanUpPAPI(EventSet, averageValues, NUM_TRIALS);

    free(A);
    free(B);
    free(C);

    return 0;
}
