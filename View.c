#include "View.h"

// Prviate functions
void drawGrid(Arena *arena);

void updateRobotVertices(Robot *robot)
{
    if (robot->direction == 'N')
    {
        robot->apex.x = robot->x * TILE_WIDTH + TILE_WIDTH / 2;
        robot->apex.y = robot->y * TILE_WIDTH;
        robot->left.x = robot->x * TILE_WIDTH;
        robot->left.y = robot->y * TILE_WIDTH + TILE_WIDTH;
        robot->right.x = robot->x * TILE_WIDTH + TILE_WIDTH;
        robot->right.y = robot->y * TILE_WIDTH + TILE_WIDTH;
    }
    else if (robot->direction == 'S')
    {
        robot->apex.x = robot->x * TILE_WIDTH + TILE_WIDTH / 2;
        robot->apex.y = robot->y * TILE_WIDTH + TILE_WIDTH;
        robot->left.x = robot->x * TILE_WIDTH;
        robot->left.y = robot->y * TILE_WIDTH;
        robot->right.x = robot->x * TILE_WIDTH + TILE_WIDTH;
        robot->right.y = robot->y * TILE_WIDTH;
    }
    else if (robot->direction == 'E')
    {
        robot->apex.x = robot->x * TILE_WIDTH + TILE_WIDTH;
        robot->apex.y = robot->y * TILE_WIDTH + TILE_WIDTH / 2;
        robot->left.x = robot->x * TILE_WIDTH;
        robot->left.y = robot->y * TILE_WIDTH;
        robot->right.x = robot->x * TILE_WIDTH;
        robot->right.y = robot->y * TILE_WIDTH + TILE_WIDTH;
    }
    else if (robot->direction == 'W')
    {
        robot->apex.x = robot->x * TILE_WIDTH;
        robot->apex.y = robot->y * TILE_WIDTH + TILE_WIDTH / 2;
        robot->left.x = robot->x * TILE_WIDTH + TILE_WIDTH;
        robot->left.y = robot->y * TILE_WIDTH + TILE_WIDTH;
        robot->right.x = robot->x * TILE_WIDTH + TILE_WIDTH;
        robot->right.y = robot->y * TILE_WIDTH;
    }
}

void drawMap(Arena *arena)
{
    background();
    clear();
    // Draw the grid first so that the tiles can be drawn on top of it
    drawGrid(arena);

    // Check each tile in the arena map
    for (int height = 0; height < arena->height; height++)
    {
        for (int width = 0; width < arena->width; width++)
        {
            // If the tile is a border tile, draw it in red
            if (arena->map[height][width] == 'B')
            {
                setColour(red);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }

            // If the tile is a marker tile, draw it in gray
            else if (arena->map[height][width] == 'M' || arena->map[height][width] == 'X')
            {
                setColour(gray);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }

            // If the tile is an obstacle tile, draw it in black
            else if (arena->map[height][width] == 'O')
            {
                setColour(black);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }
        }
    }
    return;
}

void drawGrid(Arena *arena)
{
    background();
    setColour(gray);
    // Vertical lines
    for (int i = 0; i < arena->height; i++)
    {
        drawLine(0, i * TILE_WIDTH, arena->width * TILE_WIDTH, i * TILE_WIDTH);
    }
    // Horizontal lines
    for (int i = 0; i < arena->width; i++)
    {
        drawLine(i * TILE_WIDTH, 0, i * TILE_WIDTH, arena->height * TILE_WIDTH);
    }
    return;
}

void initWindow(Arena *arena)
{
    setWindowSize(arena->width * TILE_WIDTH, arena->height * TILE_WIDTH);
    return;
}

void initView(Arena *arena, Robot *robot)
{
    initWindow(arena);
    drawMap(arena);
    updateRobotVertices(robot);
    drawRobot(robot);
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
    // Create a previous robot to preview the movement
    Robot prevrobot = *robot;
    updateRobotVertices(&prevrobot);

    int xStep = (prevrobot.apex.x - robot->apex.x) / TILE_WIDTH;
    int yStep = (prevrobot.apex.y - robot->apex.y) / TILE_WIDTH;
    if (xStep || yStep)
    {
        for (int i = 0; i < TILE_WIDTH; i++)
        {
            robot->apex.x += xStep;
            robot->apex.y += yStep;
            robot->left.x += xStep;
            robot->left.y += yStep;
            robot->right.x += xStep;
            robot->right.y += yStep;
            drawRobot(robot);
            sleep(FRAME_TIME);
        }
        updateRobotVertices(robot);
    }
    else
    {
        updateRobotVertices(robot);
        sleep(FRAME_TIME * TILE_WIDTH / 2);
        drawRobot(robot);
        sleep(FRAME_TIME * TILE_WIDTH / 2);
    }
}