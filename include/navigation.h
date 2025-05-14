#ifndef NAVIGATION_H
#define NAVIGATION_H

class navigator{
    private:
        static double fi;
        static double lambda;
        static double previous_VN, current_VN, integral_VN;
        static double previous_VE, current_VE, integral_VE;
    public:
        static void calcFi(double speedVN);
        static void calcLambda(double speedVE);
        static void setFi(double fi);
        static void setLambda(double fi);
        static double getFi();
        static double getLambda();
};

#endif