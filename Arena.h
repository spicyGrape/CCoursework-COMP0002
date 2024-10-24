#ifndef ARENA_H
#define ARENA_H
#define TILE_WIDTH 30
#define ARENA_WIDTH 14
#define ARENA_HEIGHT 10
void setupArena();

// 2D array to store the arena map
// B - Border, M - Marker, O - Obstacle, ' ' - Empty
// R - Robot, X - Robot with marker
extern char arenaMap[ARENA_HEIGHT][ARENA_WIDTH];

#endif