#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "include/data.h"
#include "include/math.h"
#include "include/matrixOperations.h"
#include "include/IMU.h"
#include "include/navigation.h"
#include "include/orientation.h"

bool alignmentFlag = false;
int takt = 1;

std::ofstream Fout("errors.txt");

int main(){

    data myData;
    std::string path = "20170922_Cessna172_200Hz_Ref.txt";
    std::ifstream Fin(path);

    if (!Fin.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    if (!Fout.is_open())
    {
       std:: cerr << "Ошибка создания файла для записи!" << std::endl;
        return 1;
    }

    //Формат данных в файле записи
    Fout << "Time\tPITCH\tROLL\tYAW\tLatitude\tLongitude\n";

    std::string line;

    // настройка ЧЭ
    IMU sensors;
    sensors.set_a_M(0.0001);
    sensors.set_d_a(0.3 * g * pow(10,-3));
    sensors.set_w_M(0.0001);
    sensors.set_w_dr(0.005 / 3600);
    sensors.setNeort(0.0001);
    while (std::getline(Fin, line)) {
        myData.parse(line);

        // std::cout   << myData.getTime() << "\t"
        //             << myData.getGyroX() << "\t"
        //             << myData.getGyroY() << "\t"
        //             << myData.getGyroZ() << "\t"
        //             << myData.getAccelX() << "\t"
        //             << myData.getAccelY() << "\t"
        //             << myData.getAccelZ() << "\t"
        //             << myData.getRoll_0() << "\t"
        //             << myData.getPitch_0() << "\t"
        //             << myData.getYaw_0() << "\t"
        //             << myData.getFi_0() << "\t"
        //             << myData.getLambda_0() << "\t"
        //             << myData.getHeight() << "\n" << std::endl;
        
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
        // std::cout << "old" << std::endl; 
        // std::cout << GyroW[0][0] << std::endl;
        // std::cout << GyroW[1][0] << std::endl;
        // std::cout << GyroW[2][0] << std::endl;
        matrix::multiply(ErrorsMatrixDUS, GyroW, GyroW);
        // std::cout << "new" << std::endl;
        // std::cout << GyroW[0][0] << std::endl;
        // std::cout << GyroW[1][0] << std::endl;
        // std::cout << GyroW[2][0] << std::endl;
        matrix::multiply(ErrorsMatrixAcc, Accel, Accel);

        double err_dus[3][1] = {sensors.get_w_dr(), sensors.get_w_dr(), sensors.get_w_dr()};
        double err_acc[3][1] = {sensors.get_d_a(), sensors.get_d_a(), sensors.get_d_a()};

        // std::cout << err_dus[0][0] << "\t" << err_dus[1][0] << "\t" << err_dus[2][0] << std::endl;

        matrix::summ(Accel, err_acc, Accel);
        // std::cout << "old" << std::endl;
        // std::cout << GyroW[0][0] << std::endl;
        // std::cout << GyroW[1][0] << std::endl;
        // std::cout << GyroW[2][0] << std::endl;
        matrix::summ(GyroW, err_dus, GyroW);
        // std::cout << "new" << std::endl; 
        // std::cout << GyroW[0][0] << std::endl;
        // std::cout << GyroW[1][0] << std::endl;
        // std::cout << GyroW[2][0] << std::endl;

        if(!alignmentFlag){
            sensors.set(myData.getRoll_0(), myData.getPitch_0(), myData.getYaw_0(), myData.getFi_0());
            navigator::setFi(degreesToRads((myData.getFi_0()))); 
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

        navigator::setFi((navigator::getFi())); // add degreesToRads()
        navigator::setLambda((navigator::getLambda())); // add degreesToRads()

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

        orientationBlock::calcC0(sensors.getCB_PL()[2][0], sensors.getCB_PL()[2][2]);
        orientationBlock::calcPitch(sensors.getCB_PL()[2][1]);
        orientationBlock::calcRoll(sensors.getCB_PL()[2][0], sensors.getCB_PL()[2][2]);
        orientationBlock::calcYaw(sensors.getCB_PL()[0][1], sensors.getCB_PL()[1][1]);

        //std::cout << "abracadabra";
        std::cout << "широта   " << radsToDegrees(navigator::getFi()) << "  долгота    " << radsToDegrees(navigator::getLambda()) << "  крен  " << orientationBlock::getPitch() << "  тангаж   " << orientationBlock::getRoll() << "  курс  " << orientationBlock::getYaw() << std::endl;

            Fout << takt << "\t"
                    << orientationBlock::getPitch() << "\t"
                    << orientationBlock::getRoll() << "\t"
                    << orientationBlock::getYaw() << "\t"
                    << radsToDegrees(navigator::getFi()) << "\t"
                    << radsToDegrees(navigator::getLambda()) << "\t"
                    << sensors.getSpeedVE() << "\t"
                    << sensors.getSpeedVN() << "\n";
    }

    Fin.close();  
    Fout.close(); 
    
    return 0;
}