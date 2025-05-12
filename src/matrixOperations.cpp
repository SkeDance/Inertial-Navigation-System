#include <iostream>
#include "../include/matrixOperations.h"
#include "../include/math.h"

void matrix::multiply(double A[3][1], double B[3][3], double C[3][1])
{
    for (int i = 0; i < 3; i++)
    {
        C[i][0] = 0;
        for (int k = 0; k < 3; k++)
        {
            C[i][0] += B[k][0] * A[i][k];
        }
    }
}

void matrix::multiply3x3(double a[3][3], double b[3][3], double result[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result[i][j] = 0;
            for (int k = 0; k < 3; ++k)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void matrix::summ(double A[3][1], double B, double C[3][1])
{
    for(int i = 0; i < 3; i++)
    {
        C[i][0] += degreesToRads(B);
    }
}



