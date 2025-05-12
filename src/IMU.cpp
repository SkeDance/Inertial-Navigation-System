#include "../include/IMU.h"
#include "../include/math.h"
#include "../include/matrixOperations.h"

void IMU::set(double roll_0, double pitch_0, double yaw_0, double fi_0){
    double matrix_0[3][3];
    matrix_0[0][0] = cos(degreesToRads(roll_0)) * cos(degreesToRads(yaw_0)) + sin(degreesToRads(pitch_0)) * sin(degreesToRads(roll_0)) * sin(degreesToRads(yaw_0));
    matrix_0[0][1] = -cos(degreesToRads(roll_0)) * sin(degreesToRads(yaw_0)) + sin(degreesToRads(pitch_0)) * sin(degreesToRads(roll_0)) * cos(degreesToRads(yaw_0));
    matrix_0[0][2] = cos(degreesToRads(pitch_0)) * sin(degreesToRads(roll_0));
    matrix_0[1][0] = cos(degreesToRads(pitch_0)) * sin(degreesToRads(yaw_0));
    matrix_0[1][1] = cos(degreesToRads(pitch_0)) * cos(degreesToRads(yaw_0));
    matrix_0[1][2] = sin(degreesToRads(pitch_0));
    matrix_0[2][0] = sin(degreesToRads(roll_0)) * cos(degreesToRads(yaw_0)) - sin(degreesToRads(pitch_0)) * cos(degreesToRads(roll_0)) * sin(degreesToRads(yaw_0));
    matrix_0[2][1] = -sin(degreesToRads(roll_0)) * sin(degreesToRads(yaw_0)) - sin(degreesToRads(pitch_0)) * cos(degreesToRads(roll_0)) * sin(degreesToRads(yaw_0));
    matrix_0[2][2] = cos(degreesToRads(pitch_0)) * cos(degreesToRads(roll_0));

    double FE = d_a / g;
    double FN = d_a / g;
    double FUp = w_dr / (degreesToRads(U) * cos(fi_0));

    double CB_PL[3][3];

    CB_PL[0][0] = 1;
    CB_PL[0][1] = -FUp;
    CB_PL[0][2] = FN;
    CB_PL[1][0] = FUp;
    CB_PL[1][1] = 1;
    CB_PL[1][2] = -FE;
    CB_PL[2][0] = -FN;
    CB_PL[2][1] = FE;
    CB_PL[2][2] = 1;

    matrix::multiply3x3(matrix_0, CB_PL, CB_PL);
}
