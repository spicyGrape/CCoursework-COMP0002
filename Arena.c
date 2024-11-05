#include "Arena.h"
#include "Agent.h"
#include "View.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// debug only
#include <time.h>

// 2D array to store the arena map
// B - Border, M - Marker, O - Obstacle, ' ' - Empty
// R - Robot, X - Robot with marker
// char arena->map[DEFAULT_ARENA_HEIGHT][arena->width] = {};

void initBorder(Arena *arena)
{
    // Set border to 'B'
    // Top and bottom border
    for (int i = 0; i < arena->width; i++)
    {
        arena->map[0][i] = 'B';
        arena->map[arena->height - 1][i] = 'B';
    }

    // Left and right border
    for (int i = 0; i < arena->height; i++)
    {
        arena->map[i][0] = 'B';
        arena->map[i][arena->width - 1] = 'B';
    }
    return;
}

void initMarkers(Arena *arena)
{
    // Set tiles with a marker to 'M'
    for (int i = 1; i < arena->height - 1; i++)
    {
        for (int j = 1; j < arena->width - 1; j++)
        {
            arena->map[i][j] = 'M';
        }
    }
    return;
}

void initObstacles(Arena *arena)
{
    // debug only
    srand(time(NULL));

    // Set obstacles to 'O'
    // Obstacles are placed randomly
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            if (arena->map[i][j] != 'B' && arena->map[i][j] != 'R')
            {
                if (rand() % 100 < 10)
                {
                    arena->map[i][j] = 'O';
                }
            }
        }
    }
    return;
}

char **initMap(Arena *arena)
{
    char **map = (char **)malloc(arena->height * sizeof(char *));
    for (int i = 0; i < arena->height; i++)
    {
        map[i] = (char *)malloc(arena->width * sizeof(char));

        // set all tiles to ' ' (empty) by default
        memset(map[i], ' ', arena->width);
    }
    return map;
}

Arena *initArena(int argc, char const **argv)
{
    Arena *arena = (Arena *)malloc(sizeof(Arena));
    if (argc >= 2)
    {
        sscanf(argv[1], "(%d,%d)", &arena->width, &arena->height);
    }
    else
    {
        arena->width = DEFAULT_ARENA_WIDTH;
        arena->height = DEFAULT_ARENA_HEIGHT;
    }
    if (argc >= 5)
    {
        sscanf(argv[4], "(%d,%d)", &arena->robotHomeX, &arena->robotHomeY);
    }
    else
    {
        arena->robotHomeX = DEFAULT_ROBOT_HOME_X;
        arena->robotHomeY = DEFAULT_ROBOT_HOME_Y;
    }

    arena->map = initMap(arena);
    // Set all tiles to ' ', representing empty tiles
    initBorder(arena);
    initMarkers(arena);
    initObstacles(arena);
    return arena;
}

void updateMap(Arena *arena, Robot *robot)
{
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            if (arena->map[i][j] == 'R')
            {
                arena->map[i][j] = ' ';
            }
            else if (arena->map[i][j] == 'X')
            {
                arena->map[i][j] = 'M';
            }
            if (i == robot->y && j == robot->x)
            {
                if (arena->map[i][j] == 'M')
                {
                    arena->map[i][j] = 'X';
                }
                else
                {
                    arena->map[i][j] = 'R';
                }
            }
        }
    }
}

int robotCanMoveForward(Arena *arena, Robot *robot)
{
    if (robot->direction == 'N')
    {
        return (arena->map[robot->y - 1][robot->x] != 'B' && arena->map[robot->y - 1][robot->x] != 'O');
    }
    else if (robot->direction == 'E')
    {
        return (arena->map[robot->y][robot->x + 1] != 'B' && arena->map[robot->y][robot->x + 1] != 'O');
    }
    else if (robot->direction == 'S')
    {
        return (arena->map[robot->y + 1][robot->x] != 'B' && arena->map[robot->y + 1][robot->x] != 'O');
    }
    else if (robot->direction == 'W')
    {
        return (arena->map[robot->y][robot->x - 1] != 'B' && arena->map[robot->y][robot->x - 1] != 'O');
    }
    return 0;
}

int robotAtMarker(Arena *arena, Robot *robot)
{
    return (arena->map[robot->y][robot->x] == 'X');
}

int robotIsAtHome(Arena *arena, Robot *robot)
{
    return (robot->x == arena->robotHomeX && robot->y == arena->robotHomeY);
}

void robotDropMarker(Arena *arena, Robot *robot)
{
    if (arena->map[robot->y][robot->x] == 'R')
    {
        arena->map[robot->y][robot->x] = 'X';
    }
    return;
}

void robotPickUpMarker(Arena *arena, Robot *robot)
{
    if (arena->map[robot->y][robot->x] == 'X')
    {
        arena->map[robot->y][robot->x] = 'R';
        robot->markers++;
    }
    return;
}

/*
main function Expecting:
1. The size of the map, including the thickness of the border: '(width, height)'
  - User is responsible for ensuring that the robot is not placed by the wall
2. Robot initial position: E, W, S, N
3. Robot initial position: '(x, y)'
4. Robot home position: '(x, y)'
*/
int main(int argc, char const **argv)
{
    Arena *arena = initArena(argc, argv);
    Robot *robot = initRobot(argc, argv, arena);
    Agent *agent = initAgent();
    updateMap(arena, robot);
    initView(arena, robot);
    while (1)
    {
        operateRobot(robot, agent);
        updateMap(arena, robot);
        drawMap(arena);
        drawMovingRobot(robot);
    }
    return 0;
}