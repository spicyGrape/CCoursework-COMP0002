#include "graphics.h"
#include "Arena.h"

char arenaMap[ARENA_HEIGHT][ARENA_WIDTH];

void initWindow()
{
    setWindowSize(ARENA_WIDTH * TILE_WIDTH, ARENA_HEIGHT * TILE_WIDTH);
    return;
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

void drawMarkers()
{
    setColour(gray);
    fillRect(7 * TILE_WIDTH, 2 * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
    return;
}

void drawArena()
{
    background();
    initWindow();
    drawGrid();
    drawBorder();
    drawMarkers();
    // drawObstacles();
}