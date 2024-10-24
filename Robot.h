#ifndef ROBOT_H
#define ROBOT_H
typedef struct
{
    // x is along the dierction of width
    int x;

    // y is height
    // y is inverted
    int y;

    // N, E, S, W
    char direction;

    int markers;
} Robot;
#include "Arena.h"

Robot *initRobot();

void forward(Robot *robot);
void left(Robot *robot);
void right(Robot *robot);
int atMarker(Robot *robot);
int canMoveForward(Robot *robot);
void pickUpMarker(Robot *robot);
void dropMarker(Robot *robot);
int markerCount(Robot *robot);

#define START_X 3
#define START_Y 3

// extern Robot robot;
#endif