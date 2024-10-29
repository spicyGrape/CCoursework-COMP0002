#ifndef AGENT_H
#define AGENT_H
#include "Robot.h"
#include <stdlib.h>
#define MEMORY_MAP_SIZE 100
typedef struct
{
    Point curPos;
    int interestsMap[MEMORY_MAP_SIZE][MEMORY_MAP_SIZE];
} Agent;
Agent *initAgent();
void operateRobot(Robot *robot, Agent *agent);
#endif