#ifndef AGENT_H
#define AGENT_H
#include "Robot.h"
#include <stdlib.h>
#define MEMORY_MAP_SIZE 30
typedef struct
{
    Point curPosition;

    // Valid values: 0, 1, 2, 3
    // Representing how many right turns from the initial direction
    int curDirection;

    // timeStampMap[HEIGHT][WIDTH]
    // All tiles are initially set to 0.
    // Recording the time stamp of the last visit
    // Borders and obstacles are set to INT_MAX
    int timeStampMap[MEMORY_MAP_SIZE][MEMORY_MAP_SIZE];
    int stepCount;
    int goingBack;
} Agent;

Agent *initAgent();
void operateRobot(Robot *robot, Agent *agent);
#endif