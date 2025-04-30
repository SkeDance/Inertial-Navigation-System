#ifndef IMU_H
#define IMU_H

#include <cmath>
#include "../include/math.h"

class IMU{
    public:
        double d_a = 1 * g * pow(10, -3);    
        double w_dr;           
        
        double w_M;                    
        double a_M;                    
        
        double err_Neort;
};

#endif