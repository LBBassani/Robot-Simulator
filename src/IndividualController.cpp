#include "IndividualController.h"
#include <cmath>
#include <iostream>

using namespace std;

IndividualController::IndividualController(Robot *r)
{
    controlledRobot = r;
    double target[] = {0,0};
    setTarget(target);
}


/*------------------------------------------------------------------------------------------------*/
void
IndividualController::setTarget(double *target)
{
    xTarget = target[0];
    yTarget = target[1];
}


/*------------------------------------------------------------------------------------------------*/
void
IndividualController::computeSpeedSetPoints()
{
    vector<double> position = controlledRobot->getState();

    currentX = position[0];
    currentY = position[1];
    currentTheta = position[2];

    auto deltaY = yTarget - currentY;
    auto deltaX = xTarget - currentX;

    auto alpha = atan2(deltaY, deltaX) - currentTheta;

    while(alpha >= M_PI)
    {
        alpha -= 2*M_PI;
    }

    while(alpha < -M_PI)
    {
        alpha += 2*M_PI;
    }

    auto distance2 = pow(deltaY, 2) + pow(deltaX, 2);
    auto rho = pow(distance2, 0.5);

    const double kU = ROBOT_MAX_SPEED_PER_WHEEL;
    const double kAlphaOmega = 7*ROBOT_MAX_SPEED_PER_WHEEL;


    double vt = kU*tanh(rho*10)*cos(alpha);
    double omega;

    if( rho > 1e-5 )
    {
        omega = kAlphaOmega*alpha + kU * (tanh(rho)/rho) * sin(2*alpha)/2;
    }
    else
    {
        auto rho2 = rho*rho;
        omega = kAlphaOmega*alpha + kU * (1 - rho2/3 + 2*rho2*rho2/15 ) * sin(2*alpha)/2;
    }

    uRightSetPoint = (vt + omega*ROBOTLEN);
    uLeftSetPoint  = (vt - omega*ROBOTLEN);

    if(fabs(uRightSetPoint) > ROBOT_MAX_SPEED_PER_WHEEL)
    {
        uRightSetPoint *= fabs(ROBOT_MAX_SPEED_PER_WHEEL/uRightSetPoint);
        uLeftSetPoint *= fabs(ROBOT_MAX_SPEED_PER_WHEEL/uRightSetPoint);
    }

    if(fabs(uLeftSetPoint) > ROBOT_MAX_SPEED_PER_WHEEL)
    {
        uRightSetPoint *= fabs(ROBOT_MAX_SPEED_PER_WHEEL/uLeftSetPoint);
        uLeftSetPoint *= fabs(ROBOT_MAX_SPEED_PER_WHEEL/uLeftSetPoint);
    }
}



/*------------------------------------------------------------------------------------------------*/
void
IndividualController::setSpeeds()
{
    computeSpeedSetPoints();
    controlledRobot->inputControls(uRightSetPoint, uLeftSetPoint);
}
