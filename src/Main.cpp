#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "WindowCallBacks.h"
#include "GLDraw.h"
#include <GL/glut.h>
#include "Constants.h"
#include "World.h"
#include <cmath>
#include "VsssUFES.h"

using namespace std;
/*------------------------------------------------------------------------------------------------*/
int
main( int argc, char ** argv )
{
    VsssUFES g("Gradle User");
    g.greet();

    const double width = 720;
    const double height = 720;
    const int simulationMaxSteps = 60*15;
    int stepCounter = 0;
    window *w = new window(width, height);
    glutInit( &argc, argv );
    initGl();


    World world;
    int robotId = 0;

    for(float theta = 0; theta < 2*M_PI; theta += (2*M_PI/10))
    {
        for(float r = 0; r < 1.2/2; r += ((1.2/2)/4))
        {
            Robot * robot = new Robot(robotId++, ROBOTLEN, r*cos(theta), r*sin(theta), -M_PI/2);
            world.insertRobot(robot);
        }
    }

    double lastTime = getCurrentTime();
    double currentTime = lastTime;

    while(true)
	{
        currentTime = getCurrentTime();
		if( !w->process( mouseFunc, keyPress, keyRelease ) ) break;

		if( ( currentTime - lastTime ) >= TIME_STEP )
		{
            if(stepCounter++ >= simulationMaxSteps) break;
            w->update();
			lastTime += TIME_STEP;
            world.evolve(TIME_STEP);
            drawAll(world);
		}
	}

    return 0;
}
