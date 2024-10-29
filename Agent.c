#include "Agent.h"

void operateRobot(Robot *robot, Agent *agent)
{
    // Forward
    if (canMoveForward(robot))
    {
        forward(robot);
    }
    // Left
    else
    {
        left(robot);
    }
    return;
}
Agent *initAgent()
{
    Agent *agent = (Agent *)malloc(sizeof(Agent));
    agent->curPos.x = MEMORY_MAP_SIZE / 2;
    agent->curPos.y = MEMORY_MAP_SIZE / 2;
    for (int i = 0; i < MEMORY_MAP_SIZE; i++)
    {
        for (int j = 0; j < MEMORY_MAP_SIZE; j++)
        {
            agent->interestsMap[i][j] = 1;
        }
    }
    return agent;
}