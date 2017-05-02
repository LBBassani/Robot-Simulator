#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "WindowCallBacks.h"
#include "GLDraw.h"
#include <GL/glut.h>

#define TIME_STEP 20
//using namespace std;

/*----------------------------------------------------------------------------*/
int
main( int argc, char ** argv )
{
    double width = 600;
    double height = 600;
    window *w = new window(width, height);
    glutInit( &argc, argv );
    initGl();

    long lastTime = getCurrentTime();
    long currentTime = lastTime;

    while(true)
	{
        currentTime = getCurrentTime();
		w->update();


		if( !w->process( mouseFunc, keyPress, keyRelease ) )
		{
			break;
		}

		if( ( currentTime - lastTime ) > TIME_STEP )
		{
			lastTime += TIME_STEP;
			processLogic();
		}
        drawAll();
	}

    return 0;
}
