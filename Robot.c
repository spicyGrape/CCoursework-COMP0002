#include "Robot.h"
#include <stdlib.h>
Robot *initRobot()
{
    Robot *robot = (Robot *)malloc(sizeof(Robot));
    robot->x = START_X;
    robot->y = START_Y;
    arenaMap[robot->y][robot->x] = 'R';
    robot->direction = 'N';
    robot->markers = 0;
    return robot;
}

void pickUpMarker(Robot *robot)
{
    if (arenaMap[robot->y][robot->x] == 'X')
    {
        arenaMap[robot->y][robot->x] = 'R';
        robot->markers++;
    }
    return;
}

void dropMarker(Robot *robot)
{
    if (arenaMap[robot->y][robot->x] == 'R')
    {
        arenaMap[robot->y][robot->x] = 'X';
        robot->markers--;
    }
    return;
}

int markerCount(Robot *robot)
{
    return robot->markers;
}

int atMarker(Robot *robot)
{
    return (arenaMap[robot->y][robot->x] == 'X');
}

void enterTile(int x, int y)
{
    if (arenaMap[y][x] == 'M')
    {
        arenaMap[y][x] = 'X';
    }
    else if (arenaMap[y][x] == ' ')
    {
        arenaMap[y][x] = 'R';
    }

    return;
}
void leaveTile(int x, int y)
{
    if (arenaMap[y][x] == 'R')
    {
        arenaMap[y][x] = ' ';
    }
    else if (arenaMap[y][x] == 'X')
    {
        arenaMap[y][x] = 'M';
    }
    return;
}

int canMoveForward(Robot *robot)
{
    if (robot->direction == 'N')
    {
        return (arenaMap[robot->y - 1][robot->x] != 'B' && arenaMap[robot->y - 1][robot->x] != 'O');
    }
    else if (robot->direction == 'E')
    {
        return (arenaMap[robot->y][robot->x + 1] != 'B' && arenaMap[robot->y][robot->x + 1] != 'O');
    }
    else if (robot->direction == 'S')
    {
        return (arenaMap[robot->y + 1][robot->x] != 'B' && arenaMap[robot->y + 1][robot->x] != 'O');
    }
    else if (robot->direction == 'W')
    {
        return (arenaMap[robot->y][robot->x - 1] != 'B' && arenaMap[robot->y][robot->x - 1] != 'O');
    }
    return 0;
}

void forward(Robot *robot)
{
    leaveTile(robot->x, robot->y);
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
    enterTile(robot->x, robot->y);
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
