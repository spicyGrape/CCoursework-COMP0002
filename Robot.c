#include "Robot.h"
#include <stdlib.h>

Robot *initRobot(int argc, char const **argv, Arena *arena)
{
    Robot *robot = (Robot *)malloc(sizeof(Robot));
    if (argc >= 3)
    {
        robot->direction = argv[2][0];
    }
    else
    {
        robot->direction = DEFAULT_START_DIRECTION;
    }
    if (argc >= 4)
    {
        sscanf(argv[3], "(%d,%d)", &robot->y, &robot->x);
    }
    else
    {
        robot->x = DEFAULT_START_X;
        robot->y = DEFAULT_START_Y;
    }
    robot->markers = 0;
    robot->arena = arena;
    return robot;
}

void pickUpMarker(Robot *robot)
{
    robotPickUpMarker(robot->arena, robot);
}

void dropMarker(Robot *robot)
{
    robotDropMarker(robot->arena, robot);
}

int markerCount(Robot *robot)
{
    return robot->markers;
}

int atMarker(Robot *robot)
{
    return robotAtMarker(robot->arena, robot);
}

int canMoveForward(Robot *robot)
{
    return robotCanMoveForward(robot->arena, robot);
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
