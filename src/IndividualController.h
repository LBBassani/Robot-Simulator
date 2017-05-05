#ifndef INDIVIDUAL_CONTROLER_H
#define INDIVIDUAL_CONTROLER_H

#include "World.h"

class IndividualController
{
private:
    World *world;
    int controledPlayerId;
    double xTarget, yTarget, thetaTarget;
    double currentX, currentY, currentTheta;
    double uRightSetPoint;
    double uLeftSetPoint;
    void computeSpeedSetPoints();
public:
    IndividualController(World *worldData, int id);
    void setTarget(double *target);
    void readState();
    void setSpeeds();
};

#endif /* INDIVIDUAL_CONTROLER_H */