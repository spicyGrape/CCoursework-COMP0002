#ifndef ARENA_H
#define ARENA_H
#define TILE_WIDTH 30
#define DEFAULT_ARENA_WIDTH 14
#define DEFAULT_ARENA_HEIGHT 10
#define MAX_ARENA_HEIGHT 20
#define MAX_ARENA_WIDTH 30
#include "Robot.h"

typedef struct arena
{
    char **map;
    int width;
    int height;
} Arena;

Arena *initArena(int argc, const char **argv);
void launchArena(int argc, const char **argv);
#endif