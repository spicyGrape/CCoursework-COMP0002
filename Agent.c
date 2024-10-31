// The agent knows nothing about the arena or robot.
// It only has access to API provided by the robot.
// So it has to keep an independent map of the arena.

#include "Agent.h"
#include <limits.h>

// Private type and variables
typedef struct
{
    int x;
    int y;
} DirectionVector;

// Private functions
DirectionVector getDirectionVector(int direction);
int lookAround(Robot *robot, Agent *agent);
void agentLeft(Robot *robot, Agent *agent);
void agentRight(Robot *robot, Agent *agent);

void operateRobot(Robot *robot, Agent *agent)
{
    if (atMarker(robot))
    {
        pickUpMarker(robot);
    }

    // Valid values: 0, 1, 2, 3
    // Representing how many right turns from the current direction
    int bestDirection = lookAround(robot, agent);

    // If bestDirection is current direction, move forward
    if (!bestDirection)
    {
        DirectionVector dVec = getDirectionVector(agent->curDirection);
        agent->curPosition.x += dVec.x;
        agent->curPosition.y += dVec.y;
        forward(robot);
        agent->stepCount++;
        agent->timeStampMap[agent->curPosition.y][agent->curPosition.x] = agent->stepCount;
    }
    else
    {
        switch (bestDirection)
        {
        case 1:
            agentRight(robot, agent);
            break;

        // Best direction is backwards
        // But agent should only call one robot API at a time
        // So just turn Right
        case 2:
            agentRight(robot, agent);
            break;
        case 3:
            agentLeft(robot, agent);
            break;
        }
    }
}

int lookAround(Robot *robot, Agent *agent)
{
    Robot testerRobot = *robot;
    int earliestStep = INT_MAX;
    int bestDirection = 2;
    for (int i = 0; i < 4; i++)
    {
        DirectionVector dVec = getDirectionVector((agent->curDirection + i) % 4);
        int *facingTileTimeStamp;
        facingTileTimeStamp = &(agent->timeStampMap[agent->curPosition.y + dVec.y][agent->curPosition.x + dVec.x]);
        if (!(canMoveForward(&testerRobot)))
        {
            *facingTileTimeStamp = INT_MAX;
        }
        if (*facingTileTimeStamp < earliestStep)
        {
            earliestStep = *facingTileTimeStamp;
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

    // Initialize the timeStampsMap
    for (int i = 0; i < MEMORY_MAP_SIZE; i++)
    {
        for (int j = 0; j < MEMORY_MAP_SIZE; j++)
        {
            agent->timeStampMap[i][j] = 0;
        }
    }
    agent->stepCount = 0;

    return agent;
}
