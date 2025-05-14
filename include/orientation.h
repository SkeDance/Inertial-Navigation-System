#ifndef ORIENTATION_H
#define ORIENTATION_H

class orientationBlock{
    public:
        static void calcC0(double A, double B);
        static void calcPitch(double A);
        static void calcRoll(double A, double B);
        static void calcYaw(double A, double B);
        static double getC0();
        static double getPitch();
        static double getRoll();
        static double getYaw();    
    private:
        static double pitch, roll, yaw;
        static double C_0;
};


#endif