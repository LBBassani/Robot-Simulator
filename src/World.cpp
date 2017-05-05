#include "World.h"
#include "GLDraw.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;

World::World()
{
    field = Field(1.5, 1.2);
}


void
World::insertRobot(Robot r)
{
    robotList.push_back(r);
}


void
World::draw()
{
    field.draw();

    for(auto it = robotList.begin(); it != robotList.end(); it++)
    {
        cout << "Draw" << endl;
        it->draw();
    }

}


void
World::evolve(double dt)
{
    for(auto it = robotList.begin(); it != robotList.end(); ++it)
    {
        it->evolve(dt);
    }
}

void
World::inputControls(int id, double u1Value, double u2Value)
{
    bool success = false;

    for(auto it = robotList.begin(); it != robotList.end(); ++it)
    {
        if(it->getId() == id)
        {
            success = true;
            it->inputControls(u1Value, u2Value);
        }
    }

    if(!success)
    {
        cout << "[WARNING] robot with id " << id << " not found" << endl;
    }

}


vector<double>
World::getState(int id, bool success)
{
    vector<double> state;
    for( auto i : robotList )
    {
        if (i.getId() == id)
        {
            success = true;
            return i.getState();
        }
    }
    success = false;
    return state;
}