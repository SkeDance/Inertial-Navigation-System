#include <iostream>
#include <cmath>
#include "../include/matrixOperations.h"
#include "../include/math.h"

void matrix::multiply(double A[3][3], double B[3][1], double C[3][1]){
    double temp[3][1] = {0};
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            temp[i][0] += B[k][0] * A[i][k];
        }
    }
    for (int i = 0; i < 3; i++){
        C[i][0] = temp[i][0];
    }
}

void matrix::multiply3x3(double a[3][3], double b[3][3], double result[3][3])
{
    double temp[3][3] = {0}; 

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            temp[i][j] = 0;
            for (int k = 0; k < 3; ++k)
            {
                temp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result[i][j] = temp[i][j];
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

void matrix::Poisson(double A[3][3], double B[3][3], double C[3][3]){
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < 3; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix::subtractMatrix(double A[3][3], double B[3][3], double C[3][3]){
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void matrix::updateMatrix(double LL[3][3], double LL_dt[3][3]){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            LL[i][j] += LL_dt[i][j] * dt;
        }
    }
}

void matrix::normalizeMatrix(double C_B_LL[3][3], int t){
    for (int i = 0; i < 3; i++)
    {
        double s;

        if (t % 2 == 0)
        { // Если такт четный, нормализация по строкам
            s = sqrt(C_B_LL[i][0] * C_B_LL[i][0] +
                     C_B_LL[i][1] * C_B_LL[i][1] +
                     C_B_LL[i][2] * C_B_LL[i][2]);

            C_B_LL[i][0] /= s;
            C_B_LL[i][1] /= s;
            C_B_LL[i][2] /= s;
        }
        else
        { // Если такт нечетный, нормализация по столбцам
            s = sqrt(C_B_LL[0][i] * C_B_LL[0][i] +
                     C_B_LL[1][i] * C_B_LL[1][i] +
                     C_B_LL[2][i] * C_B_LL[2][i]);

            C_B_LL[0][i] /= s;
            C_B_LL[1][i] /= s;
            C_B_LL[2][i] /= s;
        }
    }
}



