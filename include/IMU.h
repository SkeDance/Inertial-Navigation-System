#ifndef IMU_H
#define IMU_H

#include <cmath>
#include "../include/math.h"

class IMU{
    public:
        //set
        void set(double roll_0, double pitch_0, double yaw_0, double fi_0);
        void bodyToLocal(double A[3][3], double B[3][1], double C[3][1]);
        void calcSpeedVE(double acceleration);
        void calcSpeedVN(double acceleration);
        void calcSpeedVUp(double acceleration);
        void calcAngularWE(double VN);
        void calcAngularWN(double VE);
        void calcAngularWUp(double VE);
        void calcR_fi(double fi);
        void calcR_lambda(double fi);
        void calc_aEk();
        void calc_aNk();
        void calc_aUpk();

        //get
        double getSpeedVE();
        double getSpeedVN();
        double getSpeedVUp();
        double getAngularWE();
        double getAngularWN();
        double getAngularWUp();
        static double getR_fi();
        static double getR_lambda();
        double get_aEk();
        double get_aNk();
        double get_aUpk();

        double d_a = 1 * g * pow(10, -3);    
        double w_dr;           
        
        double w_M;                    
        double a_M;                    
        
        double err_Neort;
    private:
        double VE, VN, VUp;
        double WE, WN, WUp;
        static double R_fi, R_lambda;
        double current_aX, previous_aX;
        double current_aY, previous_aY;
        double current_aZ, previous_aZ;
        double aEk, aNk, aUPk;

};

#endif