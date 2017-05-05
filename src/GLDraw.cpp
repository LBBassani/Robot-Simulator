#include "GLDraw.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

extern int mousex, mousey;

#define BLACK (0, 0, 0)
#define RED (1, 0, 0)
#define BLUE (0, 0, 1)

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
    glColor3f BLUE;
    for( i=0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg[i]);
    }
}



/*----------------------------------------------------------------------------*/
void
drawLine(float x1, float y1, float x2, float y2)
{
    glColor3f BLACK;
    glBegin(GL_LINES);
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y2,0);
    glEnd();
}



/*----------------------------------------------------------------------------*/
void
drawRectangle(float w, float h, float x, float y, float theta, bool fill)
{
    float x1, x2, y1, y2;

    x1 = -w/2.0;
    y1 = h/2.0;
    x2 = w/2.0;
    y2 = -h/2.0;

    glPushMatrix();

    glTranslatef(x,y, 0);
    glRotatef(180*theta/M_PI, 0,0,1);

    if(fill)
    {
        glBegin(GL_QUADS);
    }
    else
    {

        glColor3f BLACK;
        glBegin(GL_LINE_LOOP);
    }

    glVertex3f(x1,y1,0);
    glVertex3f(x2,y1,0);
    glVertex3f(x2,y2,0);
    glVertex3f(x1,y2,0);
    glEnd();

    glPopMatrix();

}


/*----------------------------------------------------------------------------*/
void
drawCurve(float t0, float tf, int nPoints, double ( * fx )(double),
                                        double ( * fy )(double), double factor )
{
    if (nPoints > 1)
    {
        double delta = (tf-t0)/(nPoints-1);
        double previousT = t0;
        double currentT = t0+delta;

        for(double i = 1; i <= nPoints; ++i, currentT+=delta )
        {
            drawLine(factor*fx(previousT), factor*fy(previousT),
                                     factor*fx(currentT), factor*fy(currentT) );
            previousT = currentT;
        }
    }
    else
    {
        cout << "[WARNING] ONLY ONE POINT PROVIDED AT " << __FUNCTION__ << " CALL!";
    }
}

double sint(double x){return sin(x);}
double cost(double x){return cos(x);}



/*----------------------------------------------------------------------------*/
int extractInt( char * msg, int * consumed )
{
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
static double
extractDouble( char * msg, int * consumed )
{
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

    return  atof(buf);
}


/*----------------------------------------------------------------------------*/
void
drawEncodedForm( char * msg )
{
    double x, y;
    int consumed = 0;
    char command = msg[0];

    msg++;

    x = extractDouble(msg, &consumed );
    msg += consumed;
    //std::cout << x << "\n";
    y = extractDouble(msg, &consumed );
    msg += consumed;
    //std::cout << y << "\n\n";

    glColor3f BLACK;

    switch ( command )
    {
        case 'c':
        {
            glTranslated(x,y,0);
            double factor = extractDouble(msg, &consumed );
            msg += consumed;
            //printf("Factor = %lf\n", factor);
            drawCurve(0, 2*M_PI, 100, sint, cost, factor);
            glTranslated(-x,-y,0);
            break;
        }
        case 'l':
        {
            // to draw lines
            glColor3f BLUE;

            double xf, yf;
            xf = extractDouble(msg, &consumed );
            msg += consumed;
            //std::cout << xf << "\n";
            yf = extractDouble(msg, &consumed );
            msg += consumed;
            //std::cout << yf << "\n\n";
            drawLine(x,y,xf,yf);

            break;
        }
        case 'r':
        {
            glColor3f RED;
            glTranslated(x,y,0);

            double w = extractDouble(msg, &consumed );
            msg += consumed;
            double h = extractDouble(msg, &consumed );
            msg += consumed;
            //cout << "w = " << w << "\n";
            //cout << "h = " << h << "\n\n";
            drawRectangle(w, h, x, y, 0.0, false);

            glTranslated(-x,-y,0);

            break;
        }
    }



}



/*----------------------------------------------------------------------------*/
void drawFromFile(char * filename)
{
    FILE *fp = fopen(filename,"r");

    if(fp == NULL)
    {
        return;
    }

    char buffer[1024];
    while (!feof(fp))
    {
        fscanf(fp, "%s", buffer);
        drawEncodedForm(buffer);
    }

    fclose(fp);
}



/*----------------------------------------------------------------------------*/
void
drawAll(World &world)
{

    glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT);
    glScalef(1.2, 1.2, 1.2);

    world.draw();
    glLoadIdentity();
}
