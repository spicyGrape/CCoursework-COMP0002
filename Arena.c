#include "graphics.h"
#include "Arena.h"

char arenaMap[ARENA_HEIGHT][ARENA_WIDTH];

void initWindow()
{
    setWindowSize(ARENA_WIDTH * TILE_WIDTH, ARENA_HEIGHT * TILE_WIDTH);
}

void drawBorder()
{
    setColour(red);
    // Top border
    fillRect(0, 0, ARENA_WIDTH * TILE_WIDTH, TILE_WIDTH);
    // Bottom border
    fillRect(0, (ARENA_HEIGHT - 1) * TILE_WIDTH, ARENA_WIDTH * TILE_WIDTH, TILE_WIDTH);
    // Left border
    fillRect(0, 0, TILE_WIDTH, ARENA_HEIGHT * TILE_WIDTH);
    // Right border
    fillRect((ARENA_WIDTH - 1) * TILE_WIDTH, 0, TILE_WIDTH, ARENA_HEIGHT * TILE_WIDTH);
}

void drawArena()
{
    background();
    initWindow();
    drawBorder();
    // drawGrid();
    // drawObstacles();
    // drawMarkers();
}