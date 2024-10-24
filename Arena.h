#ifndef ARENA_H
#define ARENA_H
#define TILE_WIDTH 30
#define ARENA_WIDTH 14
#define ARENA_HEIGHT 10
void setupArena();
void NewFunction(int height, int width);
extern char arenaMap[ARENA_HEIGHT][ARENA_WIDTH] = {};
#endif