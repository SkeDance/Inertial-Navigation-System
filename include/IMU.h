#ifndef IMU_H
#define IMU_H

class IMU{
    public:
        double d_a = 1 * g * pow(10, -3);      
        double w_dr = 1 * 0.1 / 3600;           
        
        double w_M = 0.00020;                    
        double a_M = 0.00050;                    
        
        double err_Neort = 0.00010;
};

#endif