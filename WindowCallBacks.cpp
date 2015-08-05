#include "WindowCallBacks.h"
#include <stdio.h>



/*----------------------------------------------------------------------------*/
void
processLogic()
{
	// Do something
}



/*----------------------------------------------------------------------------*/
void
mouseFunc(int type, int button, int x, int y)
{
	printf("mouse - type: %d, button: %d, x: %d, y: %d\n", type, button, x, y);
}



/*----------------------------------------------------------------------------*/
void
keyPress(int code)
{
	printf("key: %d, type: press\n", code);
}



/*----------------------------------------------------------------------------*/
void
keyRelease(int code)
{
	printf("key: %d, type: release\n", code);
}
