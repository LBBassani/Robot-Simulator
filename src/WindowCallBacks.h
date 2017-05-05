#ifndef WINDOW_CALLBACKS_H
#define WINDOW_CALLBACKS_H

#include "IndividualController.h"

void processLogic(World &world, IndividualController &controller);
void mouseFunc(int type, int button, int x, int y);
void keyPress(int code);
void keyRelease(int code);

#endif /* WINDOW_CALLBACKS_H */
