#ifndef IMU_H
#define IMU_H

#include <cmath>
#include "../include/math.h"

class IMU{
    public:
        void set(double roll_0, double pitch_0, double yaw_0, double fi_0);
        double d_a = 1 * g * pow(10, -3);    
        double w_dr;           
        
        double w_M;                    
        double a_M;                    
        
        double err_Neort;
};

#endif