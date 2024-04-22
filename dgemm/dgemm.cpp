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

    m = n = k = 512;
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

    initializePAPI("PAPI_input.txt");

    int NUM_EVENTS = returnNumEventsPAPI();

    int EventSet = PAPI_NULL;
    long long values[NUM_EVENTS];
    int trials = 1; // HOW MANY TO RUN
    std::string fileName = getCurrentDateTimeString();

    // Loop for measurements

    for (int i = 0; i < trials; i++)
    {
        double *matmulOutput = matmul(A, B, C, ALPHA, BETA, m, n, k);

        stopPAPI(values, i, EventSet);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
