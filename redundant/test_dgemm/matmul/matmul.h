#ifndef ITEM_H
#define ITEM_H

#include <chrono>
#include <iostream>
#include <random>

double *matmul(double *A, double *B, double *C, int alpha, int beta, int m, int n, int k)
{

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[m * j + i] = beta * C[m * j + i];

            for (int x = 0; x < k; ++x)
            {
                C[m * j + i] += alpha * A[m * i + x] * B[k * x + j];
            }
        }
    }

    return C;
}

#endif