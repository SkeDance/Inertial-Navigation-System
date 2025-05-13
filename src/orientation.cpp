#include <cmath>
#include "../include/orientation.h"
#include "../include/math.h"

void orientationBlock::calcC0(double A, double B){
    C_0 = sqrt(A * A + B * B);
}

double orientationBlock::getC0(){
    return C_0;
}

void orientationBlock::calcPitch(double A){
    pitch = radsToDegrees(atan(A / orientationBlock::getC0()));
}

void orientationBlock::calcPitch(double A, double B){
    roll = radsToDegrees(-atan2(A, B));
}

void orientationBlock::calcYaw(double A, double B){
    yaw = normalizeAngle(radsToDegrees(atan2(A, B)));
}

double orientationBlock::getPitch(){
    return pitch;
}

double orientationBlock::getRoll(){
    return roll;
}

double orientationBlock::getYaw(){
    return yaw;
}