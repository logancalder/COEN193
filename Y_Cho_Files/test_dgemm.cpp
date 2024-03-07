#include <vector>
#include <chrono>
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
    m = 4000;
    n = 4000;
    k = 4000;
    lda = m;
    ldb = k;
    ldc = m;
    A = (double *)malloc(sizeof(double) * m * k);
#pragma omp parallel for
    for (int i = 0; i < m * k; i++)
    {
        A[i] = 0;

        double *C;
        char transA = 'N';
        char transB = 'N';
        long int m, n, k, lda, ldb, ldc;
        double ALPHA = 2;
        double BETA = 2;

        m = 4000;
        n = 4000;
        k = 4000;
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

        dgemm_(&transA, &transB, &m, &n, &k, &ALPHA, A, &lda, B, &ldb, &BETA, C, &ldc);

        free(A);
        free(B);
        free(C);

        return 0;
    }
}