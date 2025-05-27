#ifndef IMU_H
#define IMU_H

#include <cmath>
#include "../include/math.h"

class IMU{
    public:
        //set
        IMU();
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
        void set_d_a(double error);
        void set_w_dr(double error);
        void set_a_M(double error);
        void set_w_M(double error);
        void setNeort(double error);

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
        double get_d_a();
        double get_w_dr();
        double get_a_M();
        double get_w_M();
        double getNeort();
        double (&getCB_PL())[3][3]; 


    private:
        double CB_PL[3][3];
        double VE, VN, VUp;
        double WE, WN, WUp;
        static double R_fi, R_lambda;
        double current_aX, previous_aX;
        double current_aY, previous_aY;
        double current_aZ, previous_aZ;
        double aEk, aNk, aUPk;

        double d_a;      
        double w_dr;           
            
        double w_M;                    
        double a_M;                    
            
        double err_Neort;

};

#endif