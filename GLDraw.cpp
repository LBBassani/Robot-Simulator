#include "GLDraw.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>



/*----------------------------------------------------------------------------*/
void
initGl()
{

}



/*----------------------------------------------------------------------------*/
void
drawText(float x, float y, char * msg, ...)
{
    char buf[1024];
    int l,i;
    va_list args;
    va_start(args, msg);
    vsprintf(buf, msg, args);
    va_end(args);

    l = strlen(buf);
    glRasterPos2f(x, y);

    for( i=0; i < l; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buf[i]);
    }
}



/*----------------------------------------------------------------------------*/
void
drawRectangle(float x1, float y1, float x2, float y2, float z)
{
    glColor3f(1,0,0);
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z);
		glVertex3f(x2,y1,z);
		glVertex3f(x2,y2,z);
		glVertex3f(x1,y2,z);
	glEnd();
}



/*----------------------------------------------------------------------------*/
void
drawAll()
{
    glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT);
	glScalef(0.03,0.03,0.03);
	drawRectangle(-1,-1,1,1,0);
	glLoadIdentity();
}
