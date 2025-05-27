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

void matrix::summ(double A[3][1], double B[3][1], double C[3][1])
{
    for(int i = 0; i < 3; i++)
    {
        C[i][0] = A[i][0] + B[i][0];
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

void matrix::normalizeMatrix(double C_B_LL[3][3], int t) {
    // Ортогонализация по столбцам
    for (int i = 0; i < 3; ++i) {
        // Нормализация первого столбца
        double norm = sqrt(C_B_LL[0][i] * C_B_LL[0][i] + C_B_LL[1][i] * C_B_LL[1][i] + C_B_LL[2][i] * C_B_LL[2][i]);
        if (norm < 1e-10) norm = 1.0; // Защита от деления на ноль
        C_B_LL[0][i] /= norm;
        C_B_LL[1][i] /= norm;
        C_B_LL[2][i] /= norm;
    }
}



