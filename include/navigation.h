#ifndef NAVIGATION_H
#define NAVIGATION_H

class navigator{
    private:
        double fi;
        double lambda;
        double previous_VN, current_VN, integral_VN;
        double previous_VE, current_VE, integral_VE;
    public:
        void calcFi(double speedVN);
        void calcLambda(double speedVE);
        double getFi();
        double getLambda();
};

#endif