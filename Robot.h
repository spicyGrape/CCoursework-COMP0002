#ifndef ROBOT_H
#define ROBOT_H
typedef struct
{
    int x;
    int y;
} Point;
typedef struct
{
    // x is along the dierction of width
    int x;

    // y is height
    // y is inverted
    int y;

    // N, E, S, W
    char direction;

    // Managing the robot's position on screen
    Point apex;
    Point left;
    Point right;

    int markers;
} Robot;
#include "Arena.h"
#include "View.h"

Robot *initRobot();
void updateRobotVertices(Robot *robot);

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