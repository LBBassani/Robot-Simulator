#include "WindowCallBacks.h"
#include <stdio.h>
#include <stdlib.h>

const int ESC_KEY = 9;
int mousex, mousey;

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
	mousex = -100+x/3;
	mousey = 100-y/3;
}



/*----------------------------------------------------------------------------*/
void
keyPress(int code)
{
	printf("key: %d, type: press\n", code);
	if( ESC_KEY == code )
	{
		exit(0);
	}
}



/*----------------------------------------------------------------------------*/
void
keyRelease(int code)
{
	printf("key: %d, type: release\n", code);
}
