#include "Arena.h"
#include "Robot.h"
#include "Agent.h"
#include "View.h"
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

void setupArena()
{
    initMap();
    initRobot();
}
int main()
{
    setupArena();
    drawMap();
    drawGrid();

    while (1)
    {
        operateRobot();
        drawRobot();
        sleep(100);
    }
    return 0;
}