#include "Robot.h"
#include "GLDraw.h"
#include <cmath>
#include <GL/glut.h>


Robot::Robot(double LValue, double xValue, double yValue, double thetaValue)
{
    L = LValue;
    x = xValue;
    y = yValue;
    theta = thetaValue;
}

void
Robot::draw(double * rgb1, double * rgb2)
{
    double centroid1x = 0.25*L*cos(theta) + x;
    double centroid1y = 0.25*L*sin(theta) + y;

    double centroid2x = -0.25*L*cos(theta) + x;
    double centroid2y = -0.25*L*sin(theta) + y;

    glColor3dv(rgb1);
    drawRectangle(L/2, L, centroid1x, centroid1y, theta, true);
    glColor3dv(rgb2);
    drawRectangle(L/2, L, centroid2x, centroid2y, theta, true);
}

void
Robot::inputControls(double u1Value, double u2Value)
{
    u1 = u1Value;
    u2 = u2Value;
    v = 0.5*(u1 + u2);
    omega = (u1 - u2)/L;
}

static double sinc(double x)
{
    if (fabs(x) < 1e-3)
    {
        auto x2 = x*x;
        return 1 - x2/6 + x2*x2/120; // taylor series aproximation
    }
    else
    {
        return sinl(x)/x;
    }
}



void
Robot::evolve(double dt)
{
    v = 0.5*(u1 + u2);
    omega = (u1 - u2)/L;

    auto deltaTheta = omega * dt;
    auto sincValue = sinc(0.5* deltaTheta);

    auto scaleFactor = dt*v*sincValue;
    x += scaleFactor*cos(theta + 0.5*deltaTheta);
    y += scaleFactor*sin(theta + 0.5*deltaTheta);

    theta += deltaTheta;
    return;
}