#ifndef INDIVIDUAL_CONTROLER_H
#define INDIVIDUAL_CONTROLER_H

#include "Robot.h"

class IndividualController
{
private:
    Robot * controlledRobot;

    int controledPlayerId;
    double xTarget, yTarget, thetaTarget;
    double currentX, currentY, currentTheta;
    double uRightSetPoint;
    double uLeftSetPoint;
    void computeSpeedSetPoints();

public:
    IndividualController(Robot *controlledRobot);
    void setTarget(double *target);
    void setSpeeds();
};

#endif /* INDIVIDUAL_CONTROLER_H */