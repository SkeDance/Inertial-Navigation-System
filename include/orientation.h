#ifndef ORIENTATION_H
#define ORIENTATION_H

class orientationBlock{
    public:
        void calcC0(double A, double B);
        void calcPitch(double A);
        void calcPitch(double A, double B);
        void calcYaw(double A, double B);
        double getC0();
        double getPitch();
        double getRoll();
        double getYaw();    
    private:
        double pitch, roll, yaw;
        double C_0;
};


#endif