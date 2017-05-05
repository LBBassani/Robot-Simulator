#include "WindowCallBacks.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

const int ESC_KEY = 9;
int mousex, mousey;

/*----------------------------------------------------------------------------*/
void
processLogic(World &world, IndividualController &controller)
{
    static int change = 0;
    static int cnt = 0;

    controller.readState();
    if(change % 7031 == 0)
    {
        auto newXTarget = 0.5*sin(40*M_PI*cnt/1000.0);
        auto newYTarget = 0.5*cos(40*M_PI*cnt/1000.0);
        double newTarget[] = {newXTarget,newYTarget};
        controller.setTarget(newTarget);

    }

    controller.setSpeeds();
    world.evolve(TIME_STEP);

    change++;
    cnt++;
}

/*----------------------------------------------------------------------------*/
void
mouseFunc(int type, int button, int x, int y)
{
#ifdef KEY_AND_MOUSE_EVENT_VERBOSE
	printf("mouse - type: %d, button: %d, x: %d, y: %d\n", type, button, x, y);
#endif
	mousex = x;
	mousey = y;
}



/*----------------------------------------------------------------------------*/
void
keyPress(int code)
{
#ifdef KEY_AND_MOUSE_EVENT_VERBOSE
	printf("key: %d, type: press\n", code);
#endif

	if( ESC_KEY == code )
	{
		exit(0);
	}
}



/*----------------------------------------------------------------------------*/
void
keyRelease(int code)
{
#ifdef KEY_AND_MOUSE_EVENT_VERBOSE
	printf("key: %d, type: release\n", code);
#endif
}
