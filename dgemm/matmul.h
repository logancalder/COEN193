#ifndef ITEM_H
#define ITEM_H

#include <chrono>
#include <iostream>
#include <random>
#include <omp.h>

double *matmul(double *A, double *B, double *C, int alpha, int beta, int m, int n, int k)
{
    int i, j, x;
#pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            C[m * j + i] = beta * C[m * j + i];

            for (x = 0; x < k; ++x)
            {
                C[m * j + i] += alpha * A[m * i + x] * B[k * x + j];
            }
        }
    }

    return C;
}

#endif
