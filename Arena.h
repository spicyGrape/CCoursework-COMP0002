#ifndef ARENA_H
#define ARENA_H
#define TILE_WIDTH 30
#define DEFAULT_ARENA_WIDTH 14
#define DEFAULT_ARENA_HEIGHT 10
#include "Robot.h"

typedef struct arena
{
    char **map;
    int width;
    int height;
} Arena;

typedef struct robot Robot;
int robotCanMoveForward(Arena *arena, Robot *robot);
int robotAtMarker(Arena *arena, Robot *robot);
void robotDropMarker(Arena *arena, Robot *robot);
void robotPickUpMarker(Arena *arena, Robot *robot);
#endif