#include "View.h"
void drawMap()
{
    background();
    for (int height = 0; height < ARENA_HEIGHT; height++)
    {
        for (int width = 0; width < ARENA_WIDTH; width++)
        {
            if (arenaMap[height][width] == 'B')
            {
                setColour(red);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }
            else if (arenaMap[height][width] == 'M' || arenaMap[height][width] == 'X')
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
    background();
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

void initWindow()
{
    setWindowSize(ARENA_WIDTH * TILE_WIDTH, ARENA_HEIGHT * TILE_WIDTH);
    return;
}

void drawRobot()
{
    foreground();
    setColour(green);
    clear();
    if (robot.direction == 'N')
    {
        int x[3] = {robot.x * TILE_WIDTH, (robot.x + 1) * TILE_WIDTH, robot.x * TILE_WIDTH + TILE_WIDTH / 2};
        int y[3] = {(robot.y + 1) * TILE_WIDTH, (robot.y + 1) * TILE_WIDTH, robot.y * TILE_WIDTH};
        fillPolygon(3, x, y);
    }
    else if (robot.direction == 'E')
    {
        int x[3] = {robot.x * TILE_WIDTH, robot.x * TILE_WIDTH, (robot.x + 1) * TILE_WIDTH};
        int y[3] = {robot.y * TILE_WIDTH, (robot.y + 1) * TILE_WIDTH, robot.y * TILE_WIDTH + TILE_WIDTH / 2};
        fillPolygon(3, x, y);
    }
    else if (robot.direction == 'S')
    {
        int x[3] = {robot.x * TILE_WIDTH, (robot.x + 1) * TILE_WIDTH, robot.x * TILE_WIDTH + TILE_WIDTH / 2};
        int y[3] = {robot.y * TILE_WIDTH, robot.y * TILE_WIDTH, (robot.y + 1) * TILE_WIDTH};
        fillPolygon(3, x, y);
    }
    else if (robot.direction == 'W')
    {
        int x[3] = {(robot.x + 1) * TILE_WIDTH, (robot.x + 1) * TILE_WIDTH, robot.x * TILE_WIDTH};
        int y[3] = {(robot.y + 1) * TILE_WIDTH, robot.y * TILE_WIDTH, robot.y * TILE_WIDTH + TILE_WIDTH / 2};
        fillPolygon(3, x, y);
    }
}