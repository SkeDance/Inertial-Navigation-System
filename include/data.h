#ifndef DATA_H
#define DATA_H

#include <string>
#include <sstream>

class data{
    private:
        static double time;
        static double gyroX, gyroY, gyroZ;
        static double accelX, accelY, accelZ;
        static double height;
        static double roll_0, pitch_0, yaw_0;
        static double fi_0, lambda_0;
    public:
        void parse(const std::string& str);

        static double getTime();
        static double getGyroX();
        static double getGyroY();
        static double getGyroZ();
        static double getAccelX();
        static double getAccelY();
        static double getAccelZ();
        static double getHeight();
        static double getRoll_0();
        static double getPitch_0();
        static double getYaw_0();
        static double getFi_0();
        static double getLambda_0();
};

#endif