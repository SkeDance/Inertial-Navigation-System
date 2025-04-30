#include <iostream>
#include "../include/matrixOperations.h"
#include "../include/math.h"

int w;

void matrix::multiply(double A[3][1], double B[3][3], double C[3][1]){
    for (int i = 0; i < 3; i++) {
        C[i][0] = 0;
        for (int k = 0; k < 3; k++) {
            C[i][0] += B[k][0] * A[i][k]; // Суммируем все компоненты
        }
        C[i][0] += degreesToRads(w); // Добавляем дрейф после суммирования
    }
}

