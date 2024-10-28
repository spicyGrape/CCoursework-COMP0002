#include "View.h"
void drawMap()
{
    background();
    // Check each tile in the arenaMap
    for (int height = 0; height < ARENA_HEIGHT; height++)
    {
        for (int width = 0; width < ARENA_WIDTH; width++)
        {
            // If the tile is a border tile, draw it in red
            if (arenaMap[height][width] == 'B')
            {
                setColour(red);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }

            // If the tile is a marker tile, draw it in gray
            else if (arenaMap[height][width] == 'M' || arenaMap[height][width] == 'X')
            {
                setColour(gray);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }

            // If the tile is an obstacle tile, draw it in black
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

void drawRobot(Robot *robot)
{
    foreground();
    setColour(green);
    clear();
    int x[] = {robot->apex.x, robot->left.x, robot->right.x};
    int y[] = {robot->apex.y, robot->left.y, robot->right.y};
    fillPolygon(3, x, y);
}
void drawMovingRobot(Robot *robot)
{
    Robot prevrobot = *robot;
    updateRobotVertices(&prevrobot);
    int xStep = (prevrobot.apex.x - robot->apex.x) / TILE_WIDTH;
    int yStep = (prevrobot.apex.y - robot->apex.y) / TILE_WIDTH;
    for (int i = 0; i < TILE_WIDTH; i++)
    {
        robot->apex.x += xStep;
        robot->apex.y += yStep;
        robot->left.x += xStep;
        robot->left.y += yStep;
        robot->right.x += xStep;
        robot->right.y += yStep;
        drawRobot(robot);
        sleep(5);
    }
    updateRobotVertices(robot);
}