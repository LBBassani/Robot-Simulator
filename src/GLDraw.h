#ifndef GLDRAW_H
#define GLDRAW_H

#include <stdarg.h>
#include <string>

void initGl();
void drawText(float x, float y, char * msg, ...);
void drawRectangle(float w, float h, float x, float y);
void drawLine(float x1, float y1, float x2, float y2);
void drawCurve(float t0, float tf, int nPoints, double ( * fx )(double),
                                                           double ( * fy )(double), double factor );
void drawAll();

#endif /* GLDRAW_H */
