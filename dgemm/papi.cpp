#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <papi.h>
#include "matmul.h"
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

    m = n = k = 1024;
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

// Setup for PAPI
#define NUM_EVENTS 2

    int EventSet = PAPI_NULL;
    long long values[NUM_EVENTS];
    int n_events = 1; // HOW MANY TO RUN

    // MEASUREMENTS START HERE

    double average_time = 0;

    // PAPI Initialization (move outside the loop)
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
    {
        std::cerr << "PAPI initialization failed!" << std::endl;
        return 1;
    }

    // Create EventSet
    if (PAPI_create_eventset(&EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI event creation failed!" << std::endl;
        return 1;
    }

    // Add events to EventSet
    if (PAPI_add_event(EventSet, PAPI_TOT_INS) != PAPI_OK)
    {
        std::cerr << "PAPI event add failed!" << std::endl;
        return 1;
    }

    if (PAPI_add_event(EventSet, PAPI_TOT_CYC) != PAPI_OK)
    {
        std::cerr << "PAPI event add failed!" << std::endl;
        return 1;
    }

    // Loop for measurements
    for (int i = 0; i < n_events; i++)
    {
        // Start counting events
        if (PAPI_start(EventSet) != PAPI_OK)
        {
            std::cerr << "PAPI start failed!" << std::endl;
            return 1;
        }

        // Call matmul function
        double *matmulOutput = matmul(A, B, C, ALPHA, BETA, m, n, k);

        // Stop counting events
        if (PAPI_stop(EventSet, values) != PAPI_OK)
        {
            std::cerr << "PAPI stop failed!" << std::endl;
            return 1;
        }

        // FILE WRITING (should be outside the loop if you're measuring multiple iterations)
        std::string filepath = "runtime.txt";
        std::ofstream file(filepath, std::ios::app);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filepath << std::endl;
        }

        file << "# INST:\t" << values[0] << "\t|\t" << m << "x" << n << std::endl; // Write data into file
        file << "# CYCL:\t" << values[1] << "\t|\t" << m << "x" << n << std::endl; // Write data into file
        file.close();
    }

    // Cleanup
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();

    free(A);
    free(B);
    free(C);

    return 0;
}
