#ifndef DATA_H
#define DATA_H
#include <string>

class data{
    public:
        double readTime(std::string token);
        double readGyroX(std::string token);
        double readGyroY(std::string token);
        double readGyroZ(std::string token);
        double readAccelX(std::string token);
        double readAccelY(std::string token);
        double readAccelZ(std::string token);
        double readHeight(std::string token);
        double readRoll_0(std::string token);
        double readPitch_0(std::string token);
        double readYaw_0(std::string token);
        double readFi_0(std::string token);
        double readLambda_0(std::string token);
};

#endif