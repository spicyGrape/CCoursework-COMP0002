#include "Robot.h"
#include <stdlib.h>

Robot *initRobot()
{
    Robot *robot = (Robot *)malloc(sizeof(Robot));
    robot->x = START_X;
    robot->y = START_Y;
    robot->direction = 'N';
    robot->markers = 0;
    return robot;
}

void pickUpMarker(Robot *robot)
{
    robotPickUpMarker(robot);
}

void dropMarker(Robot *robot)
{
    robotDropMarker(robot);
}

int markerCount(Robot *robot)
{
    return robot->markers;
}

int atMarker(Robot *robot)
{
    return robotAtMarker(robot);
}

int canMoveForward(Robot *robot)
{
    return robotCanMoveForward(robot);
}

void forward(Robot *robot)
{
    if (robot->direction == 'N')
    {
        robot->y--;
    }
    else if (robot->direction == 'E')
    {
        robot->x++;
    }
    else if (robot->direction == 'S')
    {
        robot->y++;
    }
    else if (robot->direction == 'W')
    {
        robot->x--;
    }
    return;
}

void left(Robot *robot)
{
    if (robot->direction == 'N')
    {
        robot->direction = 'W';
    }
    else if (robot->direction == 'E')
    {
        robot->direction = 'N';
    }
    else if (robot->direction == 'S')
    {
        robot->direction = 'E';
    }
    else if (robot->direction == 'W')
    {
        robot->direction = 'S';
    }
    return;
}

void right(Robot *robot)
{
    if (robot->direction == 'N')
    {
        robot->direction = 'E';
    }
    else if (robot->direction == 'E')
    {
        robot->direction = 'S';
    }
    else if (robot->direction == 'S')
    {
        robot->direction = 'W';
    }
    else if (robot->direction == 'W')
    {
        robot->direction = 'N';
    }
    return;
}
