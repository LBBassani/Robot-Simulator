#ifndef GLDRAW_H
#define GLDRAW_H

#include <stdarg.h>

void initGl();
void drawText(float x, float y, char * msg, ...);
void drawRectangle(float x1, float y1, float x2, float y2, float z);
void drawAll();

#endif /* GLDRAW_H */
