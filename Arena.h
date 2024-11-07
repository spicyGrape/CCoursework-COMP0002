#ifndef ARENA_H
#define ARENA_H
#define TILE_WIDTH 30
#define DEFAULT_ARENA_WIDTH 14
#define DEFAULT_ARENA_HEIGHT 10
#define DEFAULT_ROBOT_HOME_X 1
#define DEFAULT_ROBOT_HOME_Y 1
#include "Robot.h"

typedef struct arena
{
    char **map;
    int width;
    int height;
    int robotHomeX;
    int robotHomeY;
} Arena;

Arena *initArena(int argc, const char **argv);
void launchArena(int argc, const char **argv);
#endif