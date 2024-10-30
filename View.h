#ifndef VIEW_H
#define VIEW_H
#include "graphics.h"
#include "Arena.h"
#include "Robot.h"
#define FRAME_TIME 5
void initView(char arenaMap[ARENA_HEIGHT][ARENA_WIDTH], Robot *robot);
void drawMap(char arenaMap[ARENA_HEIGHT][ARENA_WIDTH]);
void drawMovingRobot(Robot *robot);
void drawTurnLeft(Robot *robot);
void drawTurnRight(Robot *robot);
void drawRobot(Robot *robot);
#endif