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


/*------------------------------------------------------------------------------------------------*/
int
main( int argc, char ** argv )
{
    VsssUFES g("Gradle User");
    g.greet();

    const double width = 720;
    const double height = 720;
    window *w = new window(width, height);
    glutInit( &argc, argv );
    initGl();


    World world;
    int robotId = 0;
    Robot * robot = new Robot(robotId, ROBOTLEN, 0, 0, -M_PI/2);
    world.insertRobot(robot);

    double lastTime = getCurrentTime();
    double currentTime = lastTime;

    while(true)
	{
        currentTime = getCurrentTime();
		if( !w->process( mouseFunc, keyPress, keyRelease ) ) break;
		if( ( currentTime - lastTime ) >= TIME_STEP )
		{
            w->update();
			lastTime += TIME_STEP;
            world.evolve(TIME_STEP);
            drawAll(world);
		}
	}

    delete robot;

    return 0;
}
