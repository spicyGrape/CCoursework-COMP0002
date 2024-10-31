// The agent knows nothing about the arena or robot.
// It only has access to API provided by the robot.
// So it has to keep an independent map of the arena.

#include "Agent.h"
#include <limits.h>

// debug only
#include <stdio.h>

// Private type and variables
typedef struct
{
    int x;
    int y;
} DirectionVector;

// Private functions
DirectionVector getDirectionVector(int direction);
int findNextDirection(Robot *robot, Agent *agent);
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
    int targetDirection = findNextDirection(robot, agent);

    // If targetDirection is current direction, move forward
    if (!targetDirection)
    {
        agentForward(agent, robot);
    }
    else
    {
        rotateRobot(targetDirection, robot, agent);
    }
}

void agentForward(Agent *agent, Robot *robot)
{
    DirectionVector dVec = getDirectionVector(agent->curDirection);
    agent->curPosition.x += dVec.x;
    agent->curPosition.y += dVec.y;
    forward(robot);

    // If the agent is going back, decrement the search depth
    // Otherwise, increment the step count
    if (agent->tracingBack)
    {
        agent->searchDepth--;
        agent->tracingBack = 0;
    }
    else
    {
        agent->searchDepth++;
    }
    agent->searchDepthMap[agent->curPosition.y][agent->curPosition.x] = agent->searchDepth;
}

void rotateRobot(int targetDirection, Robot *robot, Agent *agent)
{
    switch (targetDirection)
    {
    case 1:
        agentRight(robot, agent);
        break;

    // Best direction is backwards
    // But agent should only call one robot API at a time
    // So just turn right. Turn right again in the iteration
    case 2:
        agentRight(robot, agent);
        break;
    case 3:
        agentLeft(robot, agent);
        break;
    }
}

int findNextDirection(Robot *robot, Agent *agent)
{
    Robot testerRobot = *robot;
    int backDirection = 2;
    for (int i = 0; i < 4; i++)
    {
        DirectionVector dVec = getDirectionVector((agent->curDirection + i) % 4);
        int *facingTileSearchDepth;

        // Get the search depth of the facing tile from the agent's map
        facingTileSearchDepth = &(agent->searchDepthMap[agent->curPosition.y + dVec.y][agent->curPosition.x + dVec.x]);

        if (!(canMoveForward(&testerRobot)))
        {
            *facingTileSearchDepth = INT_MAX;
        }

        // If the facing tile has not been visited
        if (!*facingTileSearchDepth)
        {
            return i;
        }

        // Mark the back direction
        if (*facingTileSearchDepth == agent->searchDepth - 1)
        {
            backDirection = i;
        }
        right(&testerRobot);
    }

    // No unvisited tile, trace back
    agent->tracingBack = 1;
    return backDirection;
}

DirectionVector getDirectionVector(int direction)
{
    DirectionVector directionVector;
    switch (direction)
    {
    case 0:
        directionVector.x = 0;
        directionVector.y = -1;
        break;
    case 1:
        directionVector.x = 1;
        directionVector.y = 0;
        break;
    case 2:
        directionVector.x = 0;
        directionVector.y = 1;
        break;
    case 3:
        directionVector.x = -1;
        directionVector.y = 0;
        break;
    default:
        // Should never reach here
        break;
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
    agent->curDirection = 0;

    // Initialize the timeStampsMap
    for (int i = 0; i < MEMORY_MAP_SIZE; i++)
    {
        for (int j = 0; j < MEMORY_MAP_SIZE; j++)
        {
            agent->searchDepthMap[i][j] = 0;
        }
    }

    agent->searchDepth = 1;
    agent->searchDepthMap[agent->curPosition.y][agent->curPosition.x] = agent->searchDepth;
    agent->tracingBack = 0;

    return agent;
}
