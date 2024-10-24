#include "graphics.h"
#include "Arena.h"

#define DEBUG
#ifdef DEBUG
// only for debugging
#include <stdio.h>
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

void initWindow()
{
    setWindowSize(ARENA_WIDTH * TILE_WIDTH, ARENA_HEIGHT * TILE_WIDTH);
    return;
}

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
#ifdef DEBUG
    printArena();
#endif
    return;
}

void drawMap()
{
    for (int height = 0; height < ARENA_HEIGHT; height++)
    {
        for (int width = 0; width < ARENA_WIDTH; width++)
        {
            if (arenaMap[height][width] == 'B')
            {
                setColour(red);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }
            else if (arenaMap[height][width] == 'M')
            {
                setColour(gray);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }
            else if (arenaMap[height][width] == 'O')
            {
                setColour(black);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }
        }
    }
    return;
}

void drawGrid()
{
    setColour(gray);
    // Vertical lines
    for (int i = 0; i < ARENA_HEIGHT; i++)
    {
        drawLine(0, i * TILE_WIDTH, ARENA_WIDTH * TILE_WIDTH, i * TILE_WIDTH);
    }
    // Horizontal lines
    for (int i = 0; i < ARENA_WIDTH; i++)
    {
        drawLine(i * TILE_WIDTH, 0, i * TILE_WIDTH, ARENA_HEIGHT * TILE_WIDTH);
    }
    return;
}

void setupArena()
{
    background();
    initWindow();
    initMap();
    drawMap();
}
int main()
{
    setupArena();
    return 0;
}