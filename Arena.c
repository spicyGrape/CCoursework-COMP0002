#include "Arena.h"
#include "Agent.h"
#include "View.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// For random obstacle generation
#include <time.h>

// Private functions
void initBorder(Arena *arena);
void initMarkers(Arena *arena);
void initObstacles(Arena *arena);
char **initMap(Arena *arena);
void updateMap(Arena *arena, Robot *robot);
void placeRobot(Arena *arena, Robot *robot);
void placeHome(Arena *arena, Robot *robot);
void checkReachable(Arena *arena, Robot *robot);
void reach(Arena *arena, Robot *robot, int x, int y);

void placeHome(Arena *arena, Robot *robot)
{
    int foundValidHome = 0;
    do
    {
        srand(time(NULL));
        int x = rand() % (arena->width - 2) + 1;
        int y = rand() % (arena->height - 2) + 1;
        if (arena->map[y][x] == ' ')
        {
            arena->map[y][x] = 'H';
            arena->robotHomeX = x;
            arena->robotHomeY = y;
            foundValidHome = 1;
        }

    } while (!foundValidHome);
    return;
}

void placeRobot(Arena *arena, Robot *robot)
{
    arena->map[robot->y][robot->x] = 'R';
    return;
}

void checkReachable(Arena *arena, Robot *robot)
{
    reach(arena, robot, robot->x, robot->y);
    return;
}

void reach(Arena *arena, Robot *robot, int x, int y)
{
    char *current_tile = &arena->map[y][x];
    if (*current_tile != 'B' && *current_tile != 'O' && *current_tile != ' ')
    {
        if (*current_tile == 0)
            *current_tile = ' ';
        reach(arena, robot, x, y - 1);
        reach(arena, robot, x + 1, y);
        reach(arena, robot, x, y + 1);
        reach(arena, robot, x - 1, y);
    }
}

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
    srand(time(NULL));

    // Set tiles with a marker to 'M'
    for (int i = 1; i < arena->height - 1; i++)
    {
        for (int j = 1; j < arena->width - 1; j++)
        {
            if (arena->map[i][j] == ' ')
            {
                if (rand() % 100 < 20)
                {
                    arena->map[i][j] = 'M';
                }
            }
        }
    }
    return;
}

void initObstacles(Arena *arena)
{
    srand(time(NULL));

    // Set obstacles to 'O'
    // Obstacles are placed randomly
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            if (arena->map[i][j] != 'B' && arena->map[i][j] != 'R' && arena->map[i][j] != 'H')
            {
                if (rand() % 100 < 20)
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
        map[i] = (char *)calloc(arena->width, sizeof(char));

    return map;
}

Arena *initArena(int argc, char const **argv, Robot *robot)
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

    // 2D char array to store the arena map, initialized to \0
    // B - Border, M - Marker, O - Obstacle, ' ' - Empty
    // R - Robot, X - Robot with marker, H - Robot home
    arena->map = initMap(arena);

    placeRobot(arena, robot);
    initBorder(arena);
    initObstacles(arena);
    checkReachable(arena, robot);
    placeHome(arena, robot);
    initMarkers(arena);
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

/*
main function Expecting:
1. The size of the map, including the thickness of the border: '(width, height)'
  - User is responsible for ensuring that the robot is not placed by the wall
2. Robot initial position: E, W, S, N
3. Robot initial position: '(x, y)'
*/
int main(int argc, char const **argv)
{
    Robot *robot = initRobot(argc, argv);
    Arena *arena = initArena(argc, argv, robot);
    Agent *agent = initAgent();
    updateMap(arena, robot);
    initView(arena, robot);
    while (operateRobot(robot, agent))
    {
        updateMap(arena, robot);
        drawMap(arena);
        drawMovingRobot(robot);
    }
    return 0;
}