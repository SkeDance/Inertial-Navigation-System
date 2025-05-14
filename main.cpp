#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "include/data.h"
#include "include/matrixOperations.h"
#include "include/IMU.h"
#include "include/navigation.h"
#include "include/orientation.h"

bool alignmentFlag = false;
//double fi;
int takt = 1;


int main(){
    // работа с файлом
    data myData;
    std::string str;

    // настройка ЧЭ
    IMU sensors;
    sensors.set_a_M(0.0001);
    sensors.set_d_a(0.3 * g * pow(10,-3));
    sensors.set_w_M(0.0001);
    sensors.set_w_dr(degreesToRads(0.005 / 3600));
    sensors.setNeort(0.0001);
    
    myData.parse(str);
    double GyroW[3][1] = {{myData.getGyroX()}, {myData.getGyroY()}, {myData.getGyroZ()}};
    double Accel[3][1] = {{myData.getAccelX()}, {myData.getAccelY()}, {myData.getAccelZ()}}; 

    double ErrorsMatrixDUS[3][3] = {
        {1.0 + sensors.get_w_M(), sensors.getNeort(), sensors.getNeort()},
        {sensors.getNeort(), 1.0 + sensors.get_w_M(), sensors.getNeort()},
        {sensors.getNeort(), sensors.getNeort(), 1.0 + sensors.get_w_M()}
    };

    double ErrorsMatrixAcc[3][3] = {
        {1.0 + sensors.get_a_M(), sensors.getNeort(), sensors.getNeort()},
        {sensors.getNeort(), 1.0 + sensors.get_a_M(), sensors.getNeort()},
        {sensors.getNeort(), sensors.getNeort(), 1.0 + sensors.get_a_M()}
    };

    matrix::multiply(ErrorsMatrixDUS, GyroW, GyroW);
    matrix::multiply(ErrorsMatrixAcc, Accel, Accel);

    matrix::summ(Accel, sensors.get_d_a(), Accel);
    matrix::summ(GyroW, sensors.get_w_dr(), GyroW);


    if(!alignmentFlag){
        sensors.set(myData.getRoll_0(), myData.getPitch_0(), myData.getYaw_0(), myData.getFi_0());
        navigator::setFi(myData.getFi_0()); 
        alignmentFlag = true;
    }

    sensors.bodyToLocal(sensors.getCB_PL(), Accel, Accel);

    sensors.calcSpeedVE(Accel[0][0]);
    sensors.calcSpeedVN(Accel[1][0]);
    sensors.calcSpeedVUp(Accel[2][0]);

    sensors.calc_aEk();
    sensors.calc_aNk();
    sensors.calc_aUpk();

    sensors.calcR_fi(navigator::getFi());
    sensors.calcR_lambda(navigator::getFi());

    sensors.calcAngularWE(sensors.getSpeedVN());
    sensors.calcAngularWN(sensors.getSpeedVE());
    sensors.calcAngularWUp(sensors.getSpeedVE());

    navigator::calcFi(sensors.getSpeedVN());
    navigator::calcLambda(sensors.getSpeedVE());

    navigator::setFi(navigator::getFi());
    navigator::setLambda(navigator::getLambda());

    double matrix_W_B[3][3] = {
        {0, -GyroW[2][0], GyroW[1][0]},
        {GyroW[2][0], 0, -GyroW[0][0]},
        {-GyroW[1][0], GyroW[0][0], 0}
    };

    double matrix_W_LL[3][3] = {
        {0, -sensors.getAngularWUp(), sensors.getAngularWN() + (0.0024 / 360 * PI / 180)},
        {sensors.getAngularWUp(), 0, -(sensors.getAngularWE() + (-0.0001 / 360 * PI / 180))},
        {-(sensors.getAngularWN() + (0.0024 / 360 * PI / 180)), (sensors.getAngularWE() + (-0.0001 / 360 * PI / 180)), 0}, 
    };

    double matrix_first[3][3];
    double matrix_second[3][3];
    double new_LL_matrix[3][3];

    matrix::Poisson(sensors.getCB_PL(), matrix_W_B, matrix_first);
    matrix::Poisson(matrix_W_LL, sensors.getCB_PL(), matrix_second);
    matrix::subtractMatrix(matrix_first, matrix_second, new_LL_matrix);

    matrix::updateMatrix(sensors.getCB_PL(), new_LL_matrix);

    matrix::normalizeMatrix(sensors.getCB_PL(), takt);
    takt++;

    orientationBlock::calcC0(sensors.getCB_PL()[2][0], sensors.getCB_PL()[2][0]);
    orientationBlock::calcPitch(sensors.getCB_PL()[2][1]);
    orientationBlock::calcRoll(sensors.getCB_PL()[2][0], sensors.getCB_PL()[2][2]);
    orientationBlock::calcYaw(sensors.getCB_PL()[0][1], sensors.getCB_PL()[1][1]);

}