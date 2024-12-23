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
        sscanf(argv[3], "(%d,%d)", &robot->x, &robot->y);
    }
    else
    {
        robot->x = DEFAULT_START_X + rand() % (arena->width - 2 * DEFAULT_START_X);
        robot->y = DEFAULT_START_Y + rand() % (arena->height - 2 * DEFAULT_START_Y);
    }
    if (argc >= 5)
    {
        sscanf(argv[4], "(%d,%d)", &robot->homeX, &robot->homeY);
    }
    else
    {
        robot->homeX = robot->x;
        robot->homeY = robot->y;
    }
    robot->markers = 0;
    robot->arena = arena;
    return robot;
}

void pickUpMarker(Robot *robot)
{
    if (robot->arena->map[robot->y][robot->x] == 'M')
    {
        robot->arena->map[robot->y][robot->x] = ' ';
        robot->markers++;
    }
    return;
}

void dropMarker(Robot *robot)
{
    if (robot->markers > 0)
    {
        robot->markers--;
        if (robot->arena->map[robot->y][robot->x] == ' ')
        {
            robot->arena->map[robot->y][robot->x] = 'M';
        }
    }
    return;
}

int markerCount(Robot *robot)
{
    return robot->markers;
}

int atMarker(Robot *robot)
{
    return (robot->arena->map[robot->y][robot->x] == 'M');
}

int canMoveForward(Robot *robot)
{
    if (robot->direction == 'N')
    {
        return (robot->arena->map[robot->y - 1][robot->x] != 'B' && robot->arena->map[robot->y - 1][robot->x] != 'O');
    }
    else if (robot->direction == 'E')
    {
        return (robot->arena->map[robot->y][robot->x + 1] != 'B' && robot->arena->map[robot->y][robot->x + 1] != 'O');
    }
    else if (robot->direction == 'S')
    {
        return (robot->arena->map[robot->y + 1][robot->x] != 'B' && robot->arena->map[robot->y + 1][robot->x] != 'O');
    }
    else if (robot->direction == 'W')
    {
        return (robot->arena->map[robot->y][robot->x - 1] != 'B' && robot->arena->map[robot->y][robot->x - 1] != 'O');
    }
    return 0;
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

int isAtHome(Robot *robot)
{
    return (robot->x == robot->homeX && robot->y == robot->homeY);
}