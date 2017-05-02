#include "Field.h"
#include <cmath>

Field::Field(double xSize, double ySize, double xCenter, double yCenter)
{
    xLen = xSize;
    yLen = ySize;
    xC = xCenter;
    yC = yCenter;
}

void
Field::draw()
{
    static float theta = 0;
    drawRectangle(xLen, yLen, xC, yC, 0, false);
    if(theta > 2*M_PI)
    {
        theta = 0.0;
    }
}