#ifndef BALL_H
#define BALL_H

#include <vector>
#include "Constants.h"

using namespace std;

class Ball
{
private:
    double x,y, vx, vy;
public:

    Ball(double xValue = 0.0, double yValue = 0.0);
    vector<double> getPosition();
    vector<double> getSpeed();
    void setSpeed(const vector<double> &speed);

    void draw();
    void evolve(double dt);

};

#endif /* BALL_H */