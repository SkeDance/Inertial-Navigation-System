#include <iostream>
#include "../include/data.h"
#include "../include/math.h"

double data::time = 0.0;
double data::gyroX = 0.0;
double data::gyroY = 0.0;
double data::gyroZ = 0.0;
double data::accelX = 0.0;
double data::accelY = 0.0;
double data::accelZ = 0.0;
double data::height = 0.0;
double data::roll_0 = 0.0;
double data::pitch_0 = 0.0;
double data::yaw_0 = 0.0;
double data::fi_0 = 0.0;
double data::lambda_0 = 0.0;

void data::parse(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    int tokenCount = 0;

    while (iss >> token) {
        switch (tokenCount) {
            case 0:  // time (предполагаем, что токены нумеруются с 0)
                time = std::stod(token);
                break;
            case 1:  // gyroX
                gyroX = std::stod(token);
                break;
            case 2:  // gyroY
                gyroY = std::stod(token);
                break;
            case 3:  // gyroZ
                gyroZ = std::stod(token);
                break;
            case 4:  // accelX
                accelX = std::stod(token);
                break;
            case 5:  // accelY
                accelY = std::stod(token);
                break;
            case 6:  // accelZ
                accelZ = std::stod(token);
                break;
            case 7:  // roll_0
                roll_0 = std::stod(token);
                break;
            case 8:  // pitch_0
                pitch_0 = std::stod(token);
                break;
            case 9: // yaw_0
                yaw_0 = std::stod(token);
                break;
            case 12: // fi_0
                fi_0 = std::stod(token);
                break;
            case 13: // lambda_0
                lambda_0 = std::stod(token);
                break;
            case 14: // height
                height = std::stod(token);
                break;
            default:
                // Игнорируем ненужные токены
                break;
        }
        tokenCount++;
    }
}
double data::getTime(){
    return time;
}

double data::getGyroX(){
    return degreesToRads(gyroX);
}

double data::getGyroY(){
    return degreesToRads(gyroY);
}

double data::getGyroZ(){
    return degreesToRads(gyroZ);
}

double data::getAccelX(){
    return accelX;
}

double data::getAccelY(){
    return accelY;
}

double data::getAccelZ(){
    return accelZ;
}

double data::getHeight(){
    return height;
}

double data::getRoll_0(){
    return roll_0;
}

double data::getPitch_0(){
    return pitch_0;
}

double data::getYaw_0(){
    return yaw_0;
}

double data::getFi_0(){
    return fi_0;
}

double data::getLambda_0(){
    return lambda_0;
}