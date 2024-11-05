#ifndef VIEW_H
#define VIEW_H
#include "graphics.h"
#include "Arena.h"
#include "Robot.h"
#define FRAME_TIME 5
typedef struct robot Robot;
typedef struct arena Arena;

// Interface
void initView(Arena *arena, Robot *robot);
void drawMap(Arena *arena);
void drawMovingRobot(Robot *robot);
void drawTurnLeft(Robot *robot);
void drawTurnRight(Robot *robot);
void drawRobot(Robot *robot);
#endif