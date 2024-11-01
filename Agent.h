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
    // All tiles are initially set to 0
    // 0 represents unexplored tiles
    // Borders and obstacles are set to INT_MAX
    int searchDepthMap[MEMORY_MAP_SIZE][MEMORY_MAP_SIZE];
    int searchDepth;
    int tracingBack;
} Agent;

Agent *initAgent();
void operateRobot(Robot *robot, Agent *agent);
void agentForward(Agent *agent, Robot *robot);
void rotateRobot(int targetDirection, Robot *robot, Agent *agent);
#endif