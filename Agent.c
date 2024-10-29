// The agent knows nothing about the arena or robot.
// It only has access to API provided by the robot.
// So it has to keep an independent map of the arena.

#include "Agent.h"

// Private type
typedef struct
{
    int x;
    int y;
} DirectionVector;

// Private functions
DirectionVector getDirectionVector(int direction);
int lookAround(Robot *robot, Agent *agent);
void updateInterestsMap(Agent *agent);
void agentLeft(Robot *robot, Agent *agent);
void agentRight(Robot *robot, Agent *agent);

void operateRobot(Robot *robot, Agent *agent)
{
    updateInterestsMap(agent);
    agent->interestsMap[agent->curPosition.y][agent->curPosition.x] = 1;
    int bestDirection = lookAround(robot, agent);
    if (!bestDirection)
    {
        DirectionVector dVec = getDirectionVector(agent->curDirection);
        agent->curPosition.x += dVec.x;
        agent->curPosition.y += dVec.y;
        forward(robot);
    }
    else
    {
        for (int i = 0; i < bestDirection; i++)
        {
            agentRight(robot, agent);
        }
    }
}

int lookAround(Robot *robot, Agent *agent)
{
    Robot testerRobot = *robot;
    int bestInterest = 0;
    int bestDirection = 2;
    for (int i = 0; i < 4; i++)
    {
        DirectionVector dVec = getDirectionVector((agent->curDirection + i) % 4);
        int *facingTileInterest;
        facingTileInterest = &(agent->interestsMap[agent->curPosition.y + dVec.y][agent->curPosition.x + dVec.x]);
        if (!(canMoveForward(&testerRobot)))
        {
            *facingTileInterest = 0;
        }
        if (*facingTileInterest > bestInterest)
        {
            bestInterest = *facingTileInterest;
            bestDirection = i;
        }
        right(&testerRobot);
    }
    return bestDirection;
}

DirectionVector getDirectionVector(int direction)
{
    DirectionVector directionVector;
    if (direction == 0)
    {
        directionVector.x = 0;
        directionVector.y = -1;
    }
    else if (direction == 1)
    {
        directionVector.x = 1;
        directionVector.y = 0;
    }
    else if (direction == 2)
    {
        directionVector.x = 0;
        directionVector.y = 1;
    }
    else if (direction == 3)
    {
        directionVector.x = -1;
        directionVector.y = 0;
    }
    return directionVector;
}

void agentLeft(Robot *robot, Agent *agent)
{
    left(robot);
    agent->curDirection = (agent->curDirection + 3) % 4;
}

void agentRight(Robot *robot, Agent *agent)
{
    right(robot);
    agent->curDirection = (agent->curDirection + 1) % 4;
}

Agent *initAgent()
{
    Agent *agent = (Agent *)malloc(sizeof(Agent));
    agent->curPosition.x = MEMORY_MAP_SIZE / 2;
    agent->curPosition.y = MEMORY_MAP_SIZE / 2;
    // Set default interest in all tiles to 1
    for (int i = 0; i < MEMORY_MAP_SIZE; i++)
    {
        for (int j = 0; j < MEMORY_MAP_SIZE; j++)
        {
            agent->interestsMap[i][j] = 1;
        }
    }
    return agent;
}

void updateInterestsMap(Agent *agent)
{
    for (int i = 0; i < MEMORY_MAP_SIZE; i++)
    {
        for (int j = 0; j < MEMORY_MAP_SIZE; j++)
        {
            if (agent->interestsMap[i][j])
            {
                agent->interestsMap[i][j] += 1;
            }
        }
    }
    return;
}