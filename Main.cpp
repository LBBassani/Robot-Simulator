#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "WindowCallBacks.h"

#define TIME_STEP 20

using namespace std;

int
main( int argc, char ** argv )
{
    window *w = new window();

    long lastTime = getCurrentTime();
    
    while(true)
	{
		w->showWindow();
		if(!w->processWindow(mouseFunc, keyPress, keyRelease))
		{
			break;
		}

		long currentTime = getCurrentTime();

		if(currentTime - lastTime > TIME_STEP)
		{
			lastTime += TIME_STEP;
			processLogic();
		}
	}

    return 0;
}
