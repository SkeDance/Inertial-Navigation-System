#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

class matrix{
    public:
        void multiply(double A[3][1], double B[3][3], double C[3][1]);
        static void multiply3x3(double A[3][3], double B[3][3], double C[3][3]);
        void summ(double A[3][1], double B, double[3][1]);
};

#endif