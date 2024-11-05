#include "View.h"

// Prviate functions
void drawGrid(Arena *arena);
void updateRobotCentre(Robot *robot);
void drawMarkerNumber(Robot *robot);

void updateRobotVertices(Robot *robot)
{
    int baseX = robot->x * TILE_WIDTH;
    int baseY = robot->y * TILE_WIDTH;
    int halfTile = TILE_WIDTH / 2;

    switch (robot->direction)
    {
    case 'N':
        robot->apex.x = baseX + halfTile;
        robot->apex.y = baseY;
        robot->left.x = baseX;
        robot->left.y = baseY + TILE_WIDTH;
        robot->right.x = baseX + TILE_WIDTH;
        robot->right.y = baseY + TILE_WIDTH;
        break;
    case 'S':
        robot->apex.x = baseX + halfTile;
        robot->apex.y = baseY + TILE_WIDTH;
        robot->left.x = baseX;
        robot->left.y = baseY;
        robot->right.x = baseX + TILE_WIDTH;
        robot->right.y = baseY;
        break;
    case 'E':
        robot->apex.x = baseX + TILE_WIDTH;
        robot->apex.y = baseY + halfTile;
        robot->left.x = baseX;
        robot->left.y = baseY;
        robot->right.x = baseX;
        robot->right.y = baseY + TILE_WIDTH;
        break;
    case 'W':
        robot->apex.x = baseX;
        robot->apex.y = baseY + halfTile;
        robot->left.x = baseX + TILE_WIDTH;
        robot->left.y = baseY + TILE_WIDTH;
        robot->right.x = baseX + TILE_WIDTH;
        robot->right.y = baseY;
        break;
    }
    updateRobotCentre(robot);
}

void drawMap(Arena *arena)
{
    background();
    clear();

    drawGrid(arena);

    for (int height = 0; height < arena->height; height++)
    {
        for (int width = 0; width < arena->width; width++)
        {
            // Border in red
            if (arena->map[height][width] == 'B')
            {
                setColour(red);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }

            // Markers in gray
            else if (arena->map[height][width] == 'M' || arena->map[height][width] == 'X')
            {
                setColour(gray);
                fillRect(width * TILE_WIDTH, height * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            }

            // Obstacles in black
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
        drawLine(0, i * TILE_WIDTH, arena->width * TILE_WIDTH, i * TILE_WIDTH);

    // Horizontal lines
    for (int i = 0; i < arena->width; i++)
        drawLine(i * TILE_WIDTH, 0, i * TILE_WIDTH, arena->height * TILE_WIDTH);

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

void updateRobotCentre(Robot *robot)
{
    if (robot->left.x == robot->right.x) // Bottom edge vertical
    {
        robot->centre.x = (robot->left.x + robot->apex.x) / 2;
    }
    else // Bottom edge horizontal
    {
        robot->centre.x = robot->apex.x;
    }

    if (robot->left.y == robot->right.y) // Bottom edge horizontal
    {
        robot->centre.y = (robot->left.y + robot->apex.y) / 2;
    }
    else // Bottom edge vertical
    {
        robot->centre.y = robot->apex.y;
    }
}

void drawRobot(Robot *robot)
{
    foreground();
    setColour(green);
    clear();
    int x[] = {robot->apex.x, robot->left.x, robot->right.x};
    int y[] = {robot->apex.y, robot->left.y, robot->right.y};
    fillPolygon(3, x, y);

    drawMarkerNumber(robot);
}

void drawMarkerNumber(Robot *robot)
{
    // Assuming number of markers less than 7 digits
    char numMarkers[8];
    sprintf(numMarkers, "%d", robot->markers);

    setColour(black);
    drawString(numMarkers, robot->centre.x, robot->centre.y);
}

void drawMovingRobot(Robot *robot)
{
    // Create a copy of robot to preview the movement
    Robot prevrobot = *robot;
    updateRobotVertices(&prevrobot);

    int xStep = (prevrobot.centre.x - robot->centre.x) / TILE_WIDTH;
    int yStep = (prevrobot.centre.y - robot->centre.y) / TILE_WIDTH;
    if (xStep || yStep) // Translation
    {
        for (int i = 0; i < TILE_WIDTH; i++)
        {
            robot->apex.x += xStep;
            robot->apex.y += yStep;
            robot->left.x += xStep;
            robot->left.y += yStep;
            robot->right.x += xStep;
            robot->right.y += yStep;
            updateRobotCentre(robot);
            drawRobot(robot);
            sleep(FRAME_TIME);
        }
        updateRobotVertices(robot);
    }
    else // Rotation
    {
        updateRobotVertices(robot);
        sleep(FRAME_TIME * TILE_WIDTH / 2);
        drawRobot(robot);
        sleep(FRAME_TIME * TILE_WIDTH / 2);
    }
}