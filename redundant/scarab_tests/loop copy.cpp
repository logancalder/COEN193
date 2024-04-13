#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "matmul.h"
#include "../../utils/scarab_markers.h"
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

    // auto start = std::chrono::high_resolution_clock::now(); // Get time start

    scarab_begin();
    double *matmulOutput = matmul(A, B, C, ALPHA, BETA, m, n, k);
    scarab_end();

    // auto end = std::chrono::high_resolution_clock::now(); // Get time end
    // auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    // int difference = duration.count(); // Record time difference

    // std::string filepath = "runtime_results.txt";
    // std::ofstream file(filepath, std::ios::app);

    // if (!file.is_open())
    // {
    // std::cerr << "Error opening file: " << filepath << std::endl;
    // }

    // file << "Trial # " << j << ": " << m << "x" << n << "," << difference << "s" << std::endl; // Write data into file
    // file.close();

    free(A);
    free(B);
    free(C);

    return 0;
}