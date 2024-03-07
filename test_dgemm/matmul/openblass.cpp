    #include <iostream>
    #include <vector>
    #include <chrono>
    #include <fstream>
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
        m = n = k = std::strtol(argv[1], nullptr, 10);
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

        // 3 loop matmul
        auto start = std::chrono::high_resolution_clock::now();

        double *matmulOutput = matmul(A, B, C, ALPHA, BETA, m, n, k);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::string filepath = "3Loop_Sq_Data.txt";
        std::ofstream file(filepath, std::ios::app);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filepath << std::endl;
            return 1;
        }

        file << m << "x" << n << "," << duration.count() << std::endl;
        file.close();

        // dgemm

        start = std::chrono::high_resolution_clock::now();

        dgemm_(&transA, &transB, &m, &n, &k, &ALPHA, A, &lda, B, &ldb, &BETA, C, &ldc);

        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (C != matmulOutput)
        {
            std::cout << "Both matrices are NOT the same!" << std::endl;
            return 1;
        }

        filepath = "Dgemm_Sq_Data.txt";
        std::ofstream second_file(filepath, std::ios::app);

        if (!second_file.is_open())
        {
            std::cerr << "Error opening file: " << filepath << std::endl;
            return 1;
        }

        second_file << m << "x" << n << "," << duration.count() << std::endl;
        second_file.close();

        free(A);
        free(B);
        free(C);
        return 0;
    }