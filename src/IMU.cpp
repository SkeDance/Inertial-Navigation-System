#include <iostream>
#include "../include/IMU.h"
#include "../include/math.h"
#include "../include/data.h"
#include "../include/matrixOperations.h"

double IMU::R_fi = 0.0;
double IMU::R_lambda = 0.0;

IMU::IMU() 
    : VE(0.0), VN(0.0), VUp(0.0),
      previous_aX(0.0), current_aX(0.0),
      previous_aY(0.0), current_aY(0.0),
      previous_aZ(0.0), current_aZ(0.0),
      aEk(0.0), aNk(0.0), aUPk(0.0)
{

}

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

void IMU::bodyToLocal(double A[3][3], double B[3][1], double C[3][1]){
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

void IMU::calcSpeedVE(double acceleration){
    previous_aX = current_aX;
    current_aX = acceleration;
    VE += ((((current_aX + previous_aX) / 2.0) + IMU::get_aEk()) * dt);
}

void IMU::calcSpeedVN(double acceleration){
    previous_aY = current_aY;
    current_aY = acceleration;
    VN += ((((current_aY + previous_aY) / 2.0) + IMU::get_aNk()) * dt);
}

void IMU::calcSpeedVUp(double acceleration){
    previous_aZ = current_aZ;
    current_aZ = acceleration;
    VUp += ((((current_aZ + previous_aZ) / 2.0) + IMU::get_aUpk()) * dt);
}

void IMU::calcR_fi(double fi){
    R_fi = (R_Earth * (1 - pow(ECC, 2))) / pow(1 - pow(ECC, 2) * pow(sin(fi), 2), 3.0 / 2.0);
}

void IMU::calcR_lambda(double fi){
    R_lambda = (R_Earth) / pow(1 - pow(ECC, 2) * pow(sin(fi), 2), 1.0 / 2.0);
}

void IMU::calcAngularWE(double VN){
    WE = (-VN / (getR_fi() + data::getHeight()));
}

void  IMU::calcAngularWN(double VE){
    WN = (VE / (getR_lambda() + data::getHeight()) + U * cos(data::getFi_0()));
}

void IMU::calcAngularWUp(double VE){
    WUp = (VE / (getR_lambda() + data::getHeight()) * tan(data::getFi_0()) + U * sin(data::getFi_0()));
}

double IMU::getAngularWE(){
    return WE;
}

double IMU::getAngularWN(){
    return WN;
}

double IMU::getAngularWUp(){
    return WUp;
}

void IMU::calc_aEk(){
    aEk = ((-IMU::getAngularWN() * IMU::getSpeedVUp()) + (IMU::getAngularWUp() * IMU::getSpeedVN()) +(-U * cos(data::getFi_0()) * IMU::getSpeedVUp()) + (U * sin(data::getFi_0()) * IMU::getSpeedVN()));
}

void IMU::calc_aNk(){
    aNk = ((-IMU::getAngularWE() * IMU::getSpeedVUp()) + (-IMU::getAngularWUp() * IMU::getSpeedVE()) + (-U * sin(data::getFi_0()) * IMU::getSpeedVE()));
}

void IMU::calc_aUpk(){
    aUPk = ((-IMU::getAngularWE() * IMU::getSpeedVN()) + (IMU::getAngularWN() * IMU::getSpeedVE()) + (U * cos(data::getFi_0()) * IMU::getSpeedVE() - g));
}

double IMU::getSpeedVE(){
    return VE;
}

double IMU::getSpeedVN(){
    return VN;
}

double IMU::getSpeedVUp(){
    return VUp;
}

double IMU::get_aEk(){
    return aEk;
}

double IMU::get_aNk(){
    return aNk;
}

double IMU::get_aUpk(){
    return aUPk;
}

double IMU::getR_fi(){
    return R_fi;
}

double IMU::getR_lambda(){
    return R_lambda;
}

double IMU::get_d_a(){
    return d_a;
}
double IMU::get_w_dr(){
    return w_dr;
}
double IMU::get_a_M(){
    return a_M;
}
double IMU::get_w_M(){
    return w_M;
}
double IMU::getNeort(){
    return err_Neort;
}

void IMU::set_d_a(double error){
    d_a = error;
}
void IMU::set_w_dr(double error){
    w_dr = degreesToRads(error);
}
void IMU::set_a_M(double error){
    a_M = error;
}
void IMU::set_w_M(double error){
    w_M = error;
}
void IMU::setNeort(double error){
    err_Neort = error;
}

double (&IMU::getCB_PL())[3][3] {
    return CB_PL;
}