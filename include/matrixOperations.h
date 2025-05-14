#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

class matrix{
    public:
        static void multiply(double A[3][3], double B[3][1], double C[3][1]);
        static void multiply3x3(double A[3][3], double B[3][3], double C[3][3]);
        static void Poisson(double A[3][3], double B[3][3], double C[3][3]);
        static void subtractMatrix(double A[3][3], double B[3][3], double C[3][3]);
        static void updateMatrix(double LL[3][3], double LL_dt[3][3]);
        static void normalizeMatrix(double C_B_LL[3][3], int t);
        static void summ(double A[3][1], double B, double[3][1]);
};

#endif