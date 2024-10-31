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
    // x is along the dierction of width
    int x;

    // y is height
    // y is inverted
    int y;

    int markers;

    // N, E, S, W
    char direction;

    // Managing the robot's position on screen
    Point apex;
    Point left;
    Point right;

    // Arena the robot is in
    Arena *arena;
} Robot;

Robot *initRobot(Arena *arena);

// Required API for the robot
void forward(Robot *robot);
void left(Robot *robot);
void right(Robot *robot);
int atMarker(Robot *robot);
int canMoveForward(Robot *robot);
void pickUpMarker(Robot *robot);
void dropMarker(Robot *robot);
int markerCount(Robot *robot);

#define START_X 4
#define START_Y 4

#endif