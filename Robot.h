#ifndef ROBOT_H
#define ROBOT_H
#include "Arena.h"

void initRobot();

void forward();
void left();
void right();
int atMarker();
int canMoveForward();
void pickUpMarker();
void dropMarker();
int markerCount();

#define START_X 3
#define START_Y 3

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
extern Robot robot;
#endif