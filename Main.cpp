#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "WindowCallBacks.h"
#include "GLDraw.h"

#define TIME_STEP 20
using namespace std;

/*----------------------------------------------------------------------------*/
int
main( int argc, char ** argv )
{
    window *w = new window();
    long lastTime = getCurrentTime();
    long currentTime = getCurrentTime();

    while(true)
	{
        currentTime = getCurrentTime();
		w->showWindow();
		if( !w->processWindow(mouseFunc, keyPress, keyRelease) )
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
