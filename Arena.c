#include "Arena.h"
#include "Agent.h"
#include "View.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// For random obstacle generation
#include <time.h>

// Private functions
void placeBorder(Arena *arena);
void placeMarkers(Arena *arena);
void placeObstacles(Arena *arena);
char **initMap(Arena *arena);
void updateRobotOnMap(Arena *arena, Robot *robot);
void freeMemory(Arena *arena, Robot *robot, Agent *agent);
void visualizeAction(Arena *arena, Robot *robot);

// 2D array to store the arena map
// B - Border, M - Marker, O - Obstacle, ' ' - Empty
// R - Robot, X - Robot with marker, H - Home, T - Robot at home
// char arena->map[DEFAULT_ARENA_HEIGHT][arena->width] = {};

void placeBorder(Arena *arena)
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

void placeMarkers(Arena *arena)
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

void placeObstacles(Arena *arena)
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

    arena->map = initMap(arena);
    placeBorder(arena);

    return arena;
}

void setUpArena(int argc, const char **argv, Arena *arena, Robot *robot)
{

    // Set all tiles to ' ', representing empty tiles
    placeMarkers(arena);
    placeObstacles(arena);
}

void updateRobotOnMap(Arena *arena, Robot *robot)
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
                char *targetTile = &arena->map[i][j];
                if (*targetTile == 'M')
                {
                    *targetTile = 'X';
                }
                else if (*targetTile == 'H')
                {
                    *targetTile = 'T';
                }
                else
                {
                    *targetTile = 'R';
                }
            }
        }
    }
}

/*
Expecting:
1. The size of the map, including the thickness of the border: '(width, height)'
  - User is responsible for ensuring that the robot is not placed by the wall
2. Robot initial position: E, W, S, N
3. Robot initial position: '(x, y)'
4. Robot home position: '(x, y)'
*/
void launchArena(int argc, const char **argv)
{
    Arena *arena = initArena(argc, argv);
    Robot *robot = initRobot(argc, argv, arena);
    setUpArena(argc, argv, arena, robot);
    Agent *agent = initAgent();
    updateRobotOnMap(arena, robot);
    initView(arena, robot);
    while (operateRobot(robot, agent))
    {
        visualizeAction(arena, robot);
    }

    // Draw the final map
    visualizeAction(arena, robot);

    // Free memory
    freeMemory(arena, robot, agent);
}

void visualizeAction(Arena *arena, Robot *robot)
{
    updateRobotOnMap(arena, robot);
    drawMap(arena);
    drawMovingRobot(robot);
}

void freeMemory(Arena *arena, Robot *robot, Agent *agent)
{
    for (int i = 0; i < arena->height; i++)
    {
        free(arena->map[i]);
    }
    free(arena->map);
    free(arena);
    free(robot);
    free(agent);
}

int main(int argc, char const **argv)
{
    launchArena(argc, argv);

    return 0;
}
