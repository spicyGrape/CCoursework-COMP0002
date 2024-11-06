#ifndef AGENT_H
#define AGENT_H
#include "Robot.h"
#include <stdlib.h>
#define MEMORY_MAP_SIZE 128
typedef struct
{
    Point curPosition;

    // Valid values: 0, 1, 2, 3
    // Representing how many right turns from the initial direction
    int curDirection;

    // searchDepthMap[HEIGHT][WIDTH]
    // Initialized to 0, representing unexplored
    // INT_MAX representing unreachable
    int searchDepthMap[MEMORY_MAP_SIZE][MEMORY_MAP_SIZE];
    int currentSearchDepth;
    int tracingBack;

    int foundHome;

    // Terminate when it reaches 3
    int terminationCounter;
} Agent;

// Interface
Agent *initAgent();
int operateRobot(Robot *robot, Agent *agent);
#endif