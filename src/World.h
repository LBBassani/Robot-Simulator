#ifndef WORLD_H
#define WORLD_H

#include "Constants.h"
#include "Robot.h"
#include "Field.h"
#include "Ball.h"
#include <vector>

using namespace std;

class World{
private:
    vector<Robot> robotList;
    Field field;
    Ball ball;
public:
    World();
    void insertRobot(Robot r);
    void draw();
    void evolve(double dt);
    void inputControls(int id, double u1Value, double u2Value);
    vector<double> getState(int id, bool &success);
    Robot getRobot(int id, bool &success);
};

#endif /* WORLD_H */