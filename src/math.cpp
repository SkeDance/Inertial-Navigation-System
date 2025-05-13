#include "../include/math.h"
#include <iostream>

double degreesToRads(double degree)
{
    return degree * PI / 180;
}

double radsToDegrees(double rads)
{
    return rads * 180 / PI;
}

double normalizeAngle(double degrees){
    const double rounding_threshold = 1e-1; // Порог 0.01°

    while (degrees < 0.0)
    {
        degrees += 360.0;
    }

    while (degrees >= 360.0)
    {
        degrees -= 360.0;
    }

    if (360.0 - degrees < rounding_threshold)
    {
        return 0.0;
    }

    return degrees;
}
