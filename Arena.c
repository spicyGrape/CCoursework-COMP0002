#include "Arena.h"
#include "Agent.h"
#include "View.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void printMap(Arena *arena, char **map)
{
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            if (map[i][j] == '\0')
            {
                printf("0");
            }
            else
                printf("%c", map[i][j]);
        }
        printf("\n");
    }
    for (;;)
        ;
}
// Private functions
void placeBorder(Arena *arena);
void placeMarkers(Arena *arena, Robot *robot);
void placeObstacles(Arena *arena, Robot *robot);
char **initMap(Arena *arena);
void freeMemory(Arena *arena, Robot *robot, Agent *agent);
void freeMap(Arena *arena);
void visualizeAction(Arena *arena, Robot *robot);
void spread(Arena *arena, int x, int y, char target);
int isValidCorrdinate(Arena *arena, int x, int y);
void trySpreadTile(Arena *arena, char currentTile, int x, int y, char target);
int robotCanreachHome(const Arena *arena, Robot *robot);
void spreadBorder(Arena *arena);
void fillAllUninitializedTiles(Arena *arena);

void fillAllUninitializedTiles(Arena *arena)
{
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            if (arena->map[i][j] == '\0')
            {
                arena->map[i][j] = arena->map[i][j - 1];
            }
        }
    }
}

void spreadBorder(Arena *arena)
{
    for (int i = 0; i < arena->width; i++)
    {
        spread(arena, i, 0, 'O');
        spread(arena, i, arena->height - 1, 'O');
    }

    for (int i = 0; i < arena->height; i++)
    {
        spread(arena, 0, i, 'O');
        spread(arena, arena->width - 1, i, 'O');
    }
}

int robotCanreachHome(const Arena *arena, Robot *robot)
{
    Arena sandbox;
    sandbox.width = arena->width;
    sandbox.height = arena->height;
    sandbox.map = initMap(&sandbox);
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            sandbox.map[i][j] = arena->map[i][j];
        }
    }
    sandbox.map[robot->y][robot->x] = ' ';
    spread(&sandbox, robot->x, robot->y, '\0');
    int canReachHome = sandbox.map[robot->homeY][robot->homeX] == ' ';
    freeMap(&sandbox);
    return canReachHome;
}

int isValidCorrdinate(Arena *arena, int x, int y)
{
    return x >= 0 && x < arena->width && y >= 0 && y < arena->height;
}

void trySpreadTile(Arena *arena, char currentTile, int x, int y, char target)
{
    if (isValidCorrdinate(arena, x, y) && arena->map[y][x] == target)
    {
        arena->map[y][x] = currentTile;
        spread(arena, x, y, target);
    }
}

void spread(Arena *arena, int x, int y, char target)
{
    char currentTile = arena->map[y][x];
    trySpreadTile(arena, currentTile, x + 1, y, target);
    trySpreadTile(arena, currentTile, x - 1, y, target);
    trySpreadTile(arena, currentTile, x, y + 1, target);
    trySpreadTile(arena, currentTile, x, y - 1, target);
}

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

void placeMarkers(Arena *arena, Robot *robot)
{
    srand(time(NULL));
    // Set tiles with a marker to 'M'
    for (int i = 1; i < arena->height - 1; i++)
    {
        for (int j = 1; j < arena->width - 1; j++)
        {
            if (arena->map[i][j] == ' ')
            {
                if (rand() % 100 < 30)
                {
                    arena->map[i][j] = 'M';
                }
            }
        }
    }
    return;
}
void placeObstacles(Arena *arena, Robot *robot)
{
    srand(time(NULL));

    // Set obstacles to 'O'
    // Obstacles are placed randomly
    for (int i = 0; i < arena->height; i++)
    {
        for (int j = 0; j < arena->width; j++)
        {
            char *targetTile = &arena->map[i][j];
            if (*targetTile != 'B' && !(i == robot->y && j == robot->x))
            {
                if (rand() % 100 < 20)
                {
                    *targetTile = 'O';
                    if (!robotCanreachHome(arena, robot))
                    {
                        *targetTile = '\0';
                    }
                }
            }
        }
    }
    return;
}

char **initMap(Arena *arena)
{
    // 2D array to store the arena map
    // B - Border, M - Marker, O - Obstacle, ' ' - Reachable tile
    // char arena->map[DEFAULT_ARENA_HEIGHT][arena->width] = {};
    char **map = (char **)malloc(arena->height * sizeof(char *));
    for (int i = 0; i < arena->height; i++)
    {
        // set all tiles to 0, representing uninitialized
        map[i] = (char *)calloc(arena->width, sizeof(char));
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
        srand(time(NULL));
        arena->width = DEFAULT_ARENA_WIDTH + rand() % (MAX_ARENA_WIDTH - DEFAULT_ARENA_WIDTH);
        arena->height = DEFAULT_ARENA_HEIGHT + rand() % (MAX_ARENA_HEIGHT - DEFAULT_ARENA_HEIGHT);
    }

    arena->map = initMap(arena);
    placeBorder(arena);

    return arena;
}

void setupArena(int argc, const char **argv, Arena *arena, Robot *robot)
{
    placeObstacles(arena, robot);

    // Mark all reachable tiles
    arena->map[robot->y][robot->x] = ' ';
    spread(arena, robot->x, robot->y, '\0');

    placeMarkers(arena, robot);
    fillAllUninitializedTiles(arena);

    // Obstacles adjacent to the border are considered as borders
    spreadBorder(arena);
}

void visualizeAction(Arena *arena, Robot *robot)
{
    drawMap(arena, robot);
    drawMovingRobot(robot);
}

void freeMemory(Arena *arena, Robot *robot, Agent *agent)
{
    freeMap(arena);
    free(arena);
    free(robot);
    free(agent);
}

void freeMap(Arena *arena)
{
    for (int i = 0; i < arena->height; i++)
    {
        free(arena->map[i]);
    }
    free(arena->map);
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
    setupArena(argc, argv, arena, robot);
    Agent *agent = initAgent();
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

int main(int argc, char const **argv)
{
    launchArena(argc, argv);

    return 0;
}
