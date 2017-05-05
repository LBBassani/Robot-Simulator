#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "WindowCallBacks.h"
#include "GLDraw.h"
#include <GL/glut.h>
#include "Constants.h"
#include "World.h"
#include <cmath>

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
    for(int id = 0; id < 1; ++ id)
    {
        Robot r(id, ROBOTLEN, id*1e-2, id*1e-2, 0.0);
        world.insertRobot(r);
    }

    long lastTime = getCurrentTime();
    long currentTime = lastTime;

    while(true)
	{
        currentTime = getCurrentTime();
		if( !w->process( mouseFunc, keyPress, keyRelease ) ) break;
		if( ( currentTime - lastTime ) > TIME_STEP )
		{
            w->update();
			lastTime += TIME_STEP;
			processLogic(world);
            drawAll(world);
		}
	}

    return 0;
}
