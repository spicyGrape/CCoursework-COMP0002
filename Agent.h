#ifndef AGENT_H
#define AGENT_H
#include "Robot.h"
#include <stdlib.h>
#define MEMORY_MAP_SIZE 100
typedef struct
{
    Point curPosition;
    int curDirection; // 0, 1, 2, 3

    // interestMap[HEIGHT][WIDTH]
    // All tiles are initially set to 1.
    // 0 means block or border
    int interestsMap[MEMORY_MAP_SIZE][MEMORY_MAP_SIZE];
} Agent;

Agent *initAgent();
void operateRobot(Robot *robot, Agent *agent);
#endif