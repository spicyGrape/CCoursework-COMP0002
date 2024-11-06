#ifndef ROBOT_H
#define ROBOT_H
#include "Arena.h"
#include "View.h"
typedef struct
{
    int x;
    int y;
} Point;

typedef struct arena Arena;
typedef struct robot
{
    // x is along the dierction of width, 0 on left
    int x;

    // y is height
    // y is inverted, 0 on top
    int y;

    int markers;

    // N, E, S, W for up, right, down, left
    char direction;

    // Managing the robot's position on screen
    // For View.c only
    Point apex;
    Point left;
    Point right;
    Point centre;

    // Arena the robot is in
    Arena *arena;
} Robot;

#include <stdio.h>
Robot *initRobot(int argc, char const **argv);

// Required API for the robot
void forward(Robot *robot);
void left(Robot *robot);
void right(Robot *robot);
int atMarker(Robot *robot);
int canMoveForward(Robot *robot);
void pickUpMarker(Robot *robot);
void dropMarker(Robot *robot);
int markerCount(Robot *robot);
int isAtHome(Robot *robot);

#define DEFAULT_START_X 4
#define DEFAULT_START_Y 4
#define DEFAULT_START_DIRECTION 'N'

#endif