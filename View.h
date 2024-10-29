#ifndef VIEW_H
#define VIEW_H
#include "graphics.h"
#include "Arena.h"
#include "Robot.h"
#define FRAME_TIME 5
void drawMap();
void drawMovingRobot(Robot *robot);
void drawTurnLeft(Robot *robot);
void drawTurnRight(Robot *robot);
void drawRobot(Robot *robot);
void drawGrid();
#endif