#include "Robot.h"
#include "Arena.h"

void initRobot()
{
    robot.x = START_X;
    robot.y = START_Y;
    arenaMap[robot.y][robot.x] = 'R';
    robot.direction = 'N';
    robot.markers = 0;
    return;
}

void pickUpMarker()
{
    if (arenaMap[robot.y][robot.x] == 'X')
    {
        arenaMap[robot.y][robot.x] = 'R';
        robot.markers++;
    }
    return;
}

void dropMarker()
{
    if (arenaMap[robot.y][robot.x] == 'R')
    {
        arenaMap[robot.y][robot.x] = 'X';
        robot.markers--;
    }
    return;
}

int markerCount()
{
    return robot.markers;
}

int atMarker()
{
    return (arenaMap[robot.y][robot.x] == 'X');
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

int canMoveForward()
{
    if (robot.direction == 'N')
    {
        return (arenaMap[robot.y - 1][robot.x] != 'B' && arenaMap[robot.y - 1][robot.x] != 'O');
    }
    else if (robot.direction == 'E')
    {
        return (arenaMap[robot.y][robot.x + 1] != 'B' && arenaMap[robot.y][robot.x + 1] != 'O');
    }
    else if (robot.direction == 'S')
    {
        return (arenaMap[robot.y + 1][robot.x] != 'B' && arenaMap[robot.y + 1][robot.x] != 'O');
    }
    else if (robot.direction == 'W')
    {
        return (arenaMap[robot.y][robot.x - 1] != 'B' && arenaMap[robot.y][robot.x - 1] != 'O');
    }
    return 0;
}

void forward()
{
    leaveTile(robot.x, robot.y);
    if (robot.direction == 'N')
    {
        robot.y--;
    }
    else if (robot.direction == 'E')
    {
        robot.x++;
    }
    else if (robot.direction == 'S')
    {
        robot.y++;
    }
    else if (robot.direction == 'W')
    {
        robot.x--;
    }
    enterTile(robot.x, robot.y);
    return;
}

void left()
{
    if (robot.direction == 'N')
    {
        robot.direction = 'W';
    }
    else if (robot.direction == 'E')
    {
        robot.direction = 'N';
    }
    else if (robot.direction == 'S')
    {
        robot.direction = 'E';
    }
    else if (robot.direction == 'W')
    {
        robot.direction = 'S';
    }
    return;
}

void right()
{
    if (robot.direction == 'N')
    {
        robot.direction = 'E';
    }
    else if (robot.direction == 'E')
    {
        robot.direction = 'S';
    }
    else if (robot.direction == 'S')
    {
        robot.direction = 'W';
    }
    else if (robot.direction == 'W')
    {
        robot.direction = 'N';
    }
    return;
}
