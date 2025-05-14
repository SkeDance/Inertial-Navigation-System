#include <iostream>
#include "../include/navigation.h"
#include "../include/data.h"
#include "../include/math.h"
#include "../include/IMU.h"

double navigator::fi = 0.0;
double navigator::lambda = 0.0;
double navigator::previous_VN = 0.0;
double navigator::current_VN = 0.0;
double navigator::integral_VN = 0.0;
double navigator::previous_VE = 0.0;
double navigator::current_VE = 0.0;
double navigator::integral_VE = 0.0;

void navigator::calcFi(double speedVN){
    previous_VN = current_VN;
    current_VN = speedVN;
    double avg_speed = ((current_VN + previous_VN) / 2.0);
    integral_VN += ((avg_speed / (IMU::getR_fi() + data::getHeight())) * dt);
    fi += data::getFi_0() + integral_VN;
}

void navigator::calcLambda(double speedVE){
    previous_VE = current_VE;
    current_VE = speedVE;
    double avg_speed = ((current_VE + previous_VE) / 2.0);
    integral_VE += ((avg_speed / ((IMU::getR_lambda() + data::getHeight()) * cos(navigator::getFi()))) * dt);
    lambda += data::getLambda_0() + integral_VE;
}

double navigator::getFi(){
    return fi;
}

double navigator::getLambda(){
    return lambda;
}

void navigator::setFi(double fi_0){
    fi = fi_0;
}
void navigator::setLambda(double lambda_0){
    lambda = lambda_0;
}
