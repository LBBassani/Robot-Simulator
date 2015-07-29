#ifndef GLDRAW_H
#define GLDRAW_H

#include <stdarg.h>

void initGl();
void drawText(float x, float y, char * msg, ...);
void drawRectangle(float w, float h, float x, float y);
void drawLine(float x1, float y1, float x2, float y2);
void drawAll();

#endif /* GLDRAW_H */
