#ifndef ARENA_H
#define ARENA_H
#define TILE_WIDTH 30
#define ARENA_WIDTH 14
#define ARENA_HEIGHT 10
#include "Robot.h"
void setupArena();
int robotCanMoveForward(Robot *robot);
int robotAtMarker(Robot *robot);
void robotDropMarker(Robot *robot);
void robotPickUpMarker(Robot *robot);
void updateMap(Robot *robot);
#endif