#include "World.h"
#include "GLDraw.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

World::World()
{
    field = Field(1.5, 1.2);
    ball = Ball(0.0, 0.0);
}

/*------------------------------------------------------------------------------------------------*/
void
World::insertRobot(Robot *controlledRobot)
{
    auto controller = new IndividualController(controlledRobot);
    robotList.push_back(controlledRobot);
    controllerList.push_back(controller);
}



/*------------------------------------------------------------------------------------------------*/
void
World::draw()
{
    field.draw();
    ball.draw();

    for(auto it = robotList.begin(); it != robotList.end(); ++it)
    {
        (*it)->draw();
    }
}



/*------------------------------------------------------------------------------------------------*/
void
World::evolve(double dt)
{
    static double elapsedTime = 0;

    for(auto it = controllerList.begin(); it != controllerList.end(); it++)
    {
        double target[] = {0.4*cos(elapsedTime), 0.4*sin(2*elapsedTime)};
        (*it)->setTarget(target);
        (*it)->setSpeeds();
    }

    for(auto it = robotList.begin(); it != robotList.end(); ++it)
    {
        (*it)->evolve(dt);
    }

    elapsedTime += dt;
}



/*------------------------------------------------------------------------------------------------*/
Robot *
World::getRobot(int id, bool &success)
{
    Robot * r = new Robot(0,ROBOTLEN,0,0,0);

    for(auto it = robotList.begin(); it != robotList.end(); ++it)
    {
        if ((*it)->getId() == id)
        {
            success = true;
            return *it;
        }
    }

    success = false;
    return r;
}