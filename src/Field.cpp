#include "Field.h"
#include"GLDraw.h"
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
    drawRectangle(xLen, yLen, xC, yC, 0, false);
    drawCurve(0, 2*M_PI, 60, cos, sin, 0.2 );
}