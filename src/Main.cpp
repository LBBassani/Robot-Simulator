#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "WindowCallBacks.h"
#include "GLDraw.h"
#include <GL/glut.h>
#include "Constants.h"
#include "World.h"
#include <cmath>
#include "IndividualController.h"

/*----------------------------------------------------------------------------*/
int
main( int argc, char ** argv )
{
    const double width = 720;
    const double height = 720;
    window *w = new window(width, height);
    glutInit( &argc, argv );
    initGl();


    World world;
    int robotId = 0;

    Robot r(robotId, ROBOTLEN, 0.4, -0.3, -M_PI/2);
    world.insertRobot(r);
    auto controller0 = IndividualController(&world, robotId);
    double target[] = {0,0};
    controller0.setTarget(target);

    long lastTime = getCurrentTime();
    long currentTime = lastTime;

    while(true)
	{
        currentTime = getCurrentTime();
		if( !w->process( mouseFunc, keyPress, keyRelease ) ) break;
		if( ( currentTime - lastTime ) >= TIME_STEP )
		{
            w->update();
			lastTime += TIME_STEP;
			processLogic(world, controller0);
            drawAll(world);
		}
	}

    return 0;
}
