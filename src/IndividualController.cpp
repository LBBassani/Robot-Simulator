#include "IndividualController.h"
#include <cmath>
#include <iostream>
//using namespace std;

IndividualController::IndividualController(World *worldData, int idValue)
{
    world = worldData;
    controledPlayerId = idValue;
}


/*------------------------------------------------------------------------------------------------*/
void
IndividualController::setTarget(double *target)
{
    xTarget = target[0];
    yTarget = target[1];
    //thetaTarget = target[2];
}


/*------------------------------------------------------------------------------------------------*/
void
IndividualController::readState()
{
    bool success = false;
    auto robot = world->getRobot(controledPlayerId, success);

    if(success)
    {
        auto state = robot.getState();
        currentX = state[0];
        currentY = state[1];
        currentTheta = state[2];
    }
    else
    {
        cout << "[WARNING] id " <<  controledPlayerId << " not found" << endl;
    }
}



/*------------------------------------------------------------------------------------------------*/
void
IndividualController::computeSpeedSetPoints()
{
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


    cout << 180*alpha/M_PI << endl;

    auto distance2 = pow(deltaY, 2) + pow(deltaX, 2);
    auto rho = pow(distance2, 0.5);
    cout << rho << "\n\n";

    const double kU = ROBOT_MAX_SPEED_PER_WHEEL;
    const double kAlphaOmega = ROBOT_MAX_SPEED_PER_WHEEL*10;


    double vt = kU*tanh(rho*10)*cos(alpha);
    double omega;

    if( rho > 1e-5 )
    {
        omega = kAlphaOmega*alpha + kU * (tanh(rho)/rho) * sin(alpha) * cos(alpha);
    }
    else
    {
        auto rho2 = rho*rho;
        omega = kAlphaOmega*alpha + kU * (1 - rho2/3 + 2*rho2*rho2/15 ) * sin(alpha) * cos(alpha);
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

    uRightSetPoint *= tanh(rho/(5*ROBOTLEN));
    uLeftSetPoint *= tanh(rho/(5*ROBOTLEN));

}



/*------------------------------------------------------------------------------------------------*/
void
IndividualController::setSpeeds()
{
    computeSpeedSetPoints();
    world->inputControls(controledPlayerId, uRightSetPoint, uLeftSetPoint);
}
