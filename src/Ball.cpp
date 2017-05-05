#include "Ball.h"
#include "GLDraw.h"
#include <GL/glut.h>
#include <cmath>

Ball::Ball(double xValue, double yValue)
{
    x = xValue;
    y = yValue;
}



/*------------------------------------------------------------------------------------------------*/
vector<double>
Ball::getPosition()
{
    vector<double> pos = {x,y};
    return pos;
}



/*------------------------------------------------------------------------------------------------*/
vector<double>
Ball::getSpeed()
{
    vector<double> speed = {vx,vy};
    return speed;
}



/*------------------------------------------------------------------------------------------------*/
void
Ball::setSpeed(const vector<double> &speed)
{
    vx = speed[0];
    vy = speed[1];
}



/*------------------------------------------------------------------------------------------------*/
void
Ball::draw()
{

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    glColor3f(1, 0.4, 0);
    for (double theta = 0.0; theta <= 2*M_PI; theta += 2*M_PI/16)
    {
        auto cX = x + BALL_RADIUS*cos(theta);
        auto cY = y + BALL_RADIUS*sin(theta);

        glVertex3f(cX, cY, 0);
    }
    auto cX = x + BALL_RADIUS;
    glVertex3f(cX, y, 0);

    glEnd();
}



/*------------------------------------------------------------------------------------------------*/
void
Ball::evolve(double dt)
{
    x += vx*dt;
    y += vy*dt;
}
