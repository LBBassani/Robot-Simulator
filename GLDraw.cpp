#include "GLDraw.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#define BLACK (0, 0, 0)

/*----------------------------------------------------------------------------*/
void
initGl()
{
}



/*----------------------------------------------------------------------------*/
void
drawText(float x, float y, const char * const msg, ...)
{
    int len,i;

    len = strlen(msg);
    glRasterPos2f(x, y);

    for( i=0; i < len; i++)
    {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg[i]);
    }
}



/*----------------------------------------------------------------------------*/
void
drawRectangle(float w, float h, float x, float y)
{
    float x1, x2, y1, y2;

    x1 = x-w/2.0;
    y1 = y+h/2.0;
    x2 = x+w/2.0;
    y2 = y-h/2.0;

    glColor3f BLACK;
    glBegin(GL_QUADS);
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y1,0);
    glVertex3f(x2,y2,0);
    glVertex3f(x1,y2,0);
    glEnd();
}



/*----------------------------------------------------------------------------*/
void
drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glColor3f BLACK;
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y2,0);
    glEnd();
}



/*----------------------------------------------------------------------------*/
void
drawCurve(float t0, float tf, int nPoints, double ( * fx )(double),
                                                       double ( * fy )(double) )
{
    if (nPoints > 1)
    {
        double delta = (tf-t0)/(nPoints-1);
        double previousT = t0;
        double currentT = t0+delta;

        for(double i = 1; i <= nPoints; ++i, currentT+=delta )
        {
            drawLine(fx(previousT), fy(previousT), fx(currentT), fy(currentT) );
            previousT = currentT;
        }
    }
}

double sint(double x){return 10*sin(x);}
double cost(double x){return 10*cos(x);}



/*----------------------------------------------------------------------------*/
int extractInt( char * msg, int * consumed )
{
    int x;

    char buf[64];
    int bufSz = 0;

    *consumed = 0;
    // find separator
    while ( msg[*consumed] != 's' )
    {
        buf[bufSz++] = msg[*consumed];
        (*consumed)++;
    }

    (*consumed)++; // 's' must be ignored on next iteration

    buf[bufSz++] = '\0';

    return  atoi(buf);
}



/*----------------------------------------------------------------------------*/
void
drawEncodedForm( char * msg )
{
    int x, y;
    int consumed = 0;
    char command = msg[0];

    msg++;

    x = extractInt(msg, &consumed );
    //std::cout << x << "\n";
    y = extractInt(msg + consumed, &consumed );
    //std::cout << y << "\n\n";

    switch ( command )
    {
        case 'c':
        {
            msg++;
            glColor3f BLACK;
            glTranslated(x,y,0);
            drawCurve(0, 2*M_PI, 200, sint, cost);
            glTranslated(-x,-y,0);
            break;
        }
        case 'l':
        {
            msg++;
            // to draw lines
            break;
        }
        case 'r':
        {
            msg++;
            drawRectangle(10, 10, x, y);
            break;
        }
    }


}



/*----------------------------------------------------------------------------*/
void
drawAll()
{
    glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT);
    glScalef(0.03,0.03,0.03);
    //drawRectangle(10,1,-10,-5);
    //drawLine(2,-2,-2,2);
    //drawCurve(0, 2*M_PI, 200, sint, cost);

    //const char * const str = "Hello world!!!";
    //drawText(3, 3, str);
    drawEncodedForm("c5s5s");

    glLoadIdentity();
}
