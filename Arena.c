#include "Arena.h"
#include "Robot.h"
#include "Agent.h"
#include "View.h"

// 2D array to store the arena map
// B - Border, M - Marker, O - Obstacle, ' ' - Empty
// R - Robot, X - Robot with marker
char arenaMap[ARENA_HEIGHT][ARENA_WIDTH] = {};

#define DEBUG
#ifdef DEBUG
// only for debugging
#include <stdio.h>
#include <stdlib.h>
void printArena()
{
    for (int i = 0; i < ARENA_HEIGHT; i++)
    {
        for (int j = 0; j < ARENA_WIDTH; j++)
        {
            printf("%c", arenaMap[i][j]);
        }
        printf("\n");
    }
    return;
}
#endif

void initBorder()
{
    // Set border to 'B'
    // Top and bottom border
    for (int i = 0; i < ARENA_WIDTH; i++)
    {
        arenaMap[0][i] = 'B';
        arenaMap[ARENA_HEIGHT - 1][i] = 'B';
    }
    // Left and right border
    for (int i = 0; i < ARENA_HEIGHT; i++)
    {
        arenaMap[i][0] = 'B';
        arenaMap[i][ARENA_WIDTH - 1] = 'B';
    }
    return;
}

void initMarkers()
{
    // Set markers to 'M'
    arenaMap[2][7] = 'M';
    return;
}

void initObstacles()
{
    return;
}

void initMap()
{
    // Set all tiles to ' ', representing empty tiles
    for (int i = 0; i < ARENA_HEIGHT; i++)
    {
        for (int j = 0; j < ARENA_WIDTH; j++)
        {
            arenaMap[i][j] = ' ';
        }
    }
    initBorder();
    initObstacles();
    initMarkers();
    return;
}

void updateMap(Robot *robot)
{
    for (int i = 0; i < ARENA_HEIGHT; i++)
    {
        for (int j = 0; j < ARENA_WIDTH; j++)
        {
            if (arenaMap[i][j] == 'R')
            {
                arenaMap[i][j] = ' ';
            }
            else if (arenaMap[i][j] == 'X')
            {
                arenaMap[i][j] = 'M';
            }
            if (i == robot->y && j == robot->x)
            {
                if (arenaMap[i][j] == 'M')
                {
                    arenaMap[i][j] = 'X';
                }
                else
                {
                    arenaMap[i][j] = 'R';
                }
            }
        }
    }
}
int robotCanMoveForward(Robot *robot)
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
int robotAtMarker(Robot *robot)
{
    return (arenaMap[robot->y][robot->x] == 'X');
}
void robotDropMarker(Robot *robot)
{
    if (arenaMap[robot->y][robot->x] == 'R')
    {
        arenaMap[robot->y][robot->x] = 'X';
        robot->markers--;
    }
    return;
}

void robotPickUpMarker(Robot *robot)
{
    if (arenaMap[robot->y][robot->x] == 'X')
    {
        arenaMap[robot->y][robot->x] = 'R';
        robot->markers++;
    }
    return;
}

int main()
{
    initMap();
    Robot *robot = initRobot();
    Agent *agent = initAgent();
    updateMap(robot);
    initView(arenaMap, robot);
    while (1)
    {
        operateRobot(robot, agent);
        updateMap(robot);
        drawMovingRobot(robot);
    }
    return 0;
}