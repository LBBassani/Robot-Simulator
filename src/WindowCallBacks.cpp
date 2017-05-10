#include "WindowCallBacks.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

const int ESC_KEY = 9;
int mousex, mousey;

/*----------------------------------------------------------------------------*/
void
processLogic()
{

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
