#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
// #include <omp.h>
#include "/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/Parallel-Algorithms-Analysis/perf.h"
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

    m = n = k = 256;
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
    int n_threads = omp_get_max_threads();
    int *event_sets = (int *)malloc(n_threads * sizeof(int));

    std::vector<std::string> events;
    int n_events = 10; // HOW MANY TO RUN

    int ret = PAPI_library_init(PAPI_VER_CURRENT);
    if (ret != PAPI_VER_CURRENT)
    {
        fprintf(stderr, "Error inititalizing PAPI: %s\n", PAPI_strerror(ret));
    }

    // MEASUREMENTS START HERE

    double average_time = 0;

    for (int i = 0; i < n_events; i++)
    {
        papi_profile_start(event_sets, events.at(i), false);
        double start, end;
        start = omp_get_wtime();

        // vvvvvvvvvvvvvvv

        double *matmulOutput = matmul(A, B, C, ALPHA, BETA, m, n, k);

        // ^^^^^^^^^^^^^^^

        end = omp_get_wtime();
        average_time += end - start;
        papi_profile_end(n_threads, event_sets, events.at(i), false);

        // FILE WRITING
        std::string filepath = "runtime.txt";
        std::ofstream file(filepath, std::ios::app);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filepath << std::endl;
        }

        file << "TRIAL #:\t" << i << "\t:\t" << m << "x" << n << "\t" << average_time << std::endl; // Write data into file
        file.close();
    }

    PAPI_shutdown();
    // File writing

    free(event_sets);
    free(A);
    free(B);
    free(C);

    return 0;
}