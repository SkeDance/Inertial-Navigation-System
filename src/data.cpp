#include "../include/data.h"
#include <iostream>

void data::parse(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    int tokenCount = 0;

    while (iss >> token) {
        switch (tokenCount) {
            case 1:  // time (предполагаем, что токены нумеруются с 0)
                time = std::stod(token);
                break;
            case 2:  // gyroX
                gyroX = std::stod(token);
                break;
            case 3:  // gyroY
                gyroY = std::stod(token);
                break;
            case 4:  // gyroZ
                gyroZ = std::stod(token);
                break;
            case 5:  // accelX
                accelX = std::stod(token);
                break;
            case 6:  // accelY
                accelY = std::stod(token);
                break;
            case 7:  // accelZ
                accelZ = std::stod(token);
                break;
            case 8:  // roll_0
                roll_0 = std::stod(token);
                break;
            case 9:  // pitch_0
                pitch_0 = std::stod(token);
                break;
            case 10: // yaw_0
                yaw_0 = std::stod(token);
                break;
            case 13: // fi_0
                fi_0 = std::stod(token);
                break;
            case 14: // lambda_0
                lambda_0 = std::stod(token);
                break;
            case 15: // height
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
    return gyroX;
}

double data::getGyroY(){
    return gyroY;
}

double data::getGyroZ(){
    return gyroZ;
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