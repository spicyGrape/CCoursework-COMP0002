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
int findNextDirection(Robot *robot, Agent *agent);
void agentLeft(Robot *robot, Agent *agent);
void agentRight(Robot *robot, Agent *agent);
void agentForward(Agent *agent, Robot *robot);
void rotateRobot(int targetDirection, Robot *robot, Agent *agent);
void resetSearchMap(Agent *agent);
void checkRobotAtHome(Robot *robot, Agent *agent);
void checkRobotAtMarker(Robot *robot);
int checkTerminalCondition(Robot *robot, Agent *agent);

int operateRobot(Robot *robot, Agent *agent)
{
    checkRobotAtHome(robot, agent);
    checkRobotAtMarker(robot);

    // Valid values: 0, 1, 2, 3
    // Representing how many right turns from the current direction
    int targetDirection = findNextDirection(robot, agent);

    if (!targetDirection)
        agentForward(agent, robot);
    else
        rotateRobot(targetDirection, robot, agent);

    return !(checkTerminalCondition(robot, agent));
}

void checkRobotAtMarker(Robot *robot)
{
    if (atMarker(robot))
    {
        if (!isAtHome(robot))
            pickUpMarker(robot);
    }
}

void checkRobotAtHome(Robot *robot, Agent *agent)
{
    if (isAtHome(robot))
    {
        if (!agent->foundHome)
        {
            agent->foundHome = 1;

            // reset the search map
            // so that the home becomes the root of the search tree
            resetSearchMap(agent);
        }
        else if (robot->markers > 0)
            dropMarker(robot);
    }
}

void agentForward(Agent *agent, Robot *robot)
{
    agent->consecutiveTurns = 0;

    DirectionVector dVec = getDirectionVector(agent->curDirection);
    agent->curPosition.x += dVec.x;
    agent->curPosition.y += dVec.y;
    forward(robot);

    if (agent->tracingBack)
    {
        agent->currentSearchDepth--;
        agent->tracingBack = 0;
    }
    else
    {
        agent->currentSearchDepth++;
    }
    agent->searchDepthMap[agent->curPosition.y][agent->curPosition.x] = agent->currentSearchDepth;
}

void rotateRobot(int targetDirection, Robot *robot, Agent *agent)
{
    agent->consecutiveTurns++;

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
    // An instance of DFS
    // Trace back by count back from the current search depth

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
        if (*facingTileSearchDepth == agent->currentSearchDepth - 1)
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
    agent->foundHome = 0;
    agent->consecutiveTurns = 0;

    // Initialize the Search Depth Map
    resetSearchMap(agent);

    return agent;
}

void resetSearchMap(Agent *agent)
{
    for (int i = 0; i < MEMORY_MAP_SIZE; i++)
    {
        for (int j = 0; j < MEMORY_MAP_SIZE; j++)
        {
            agent->searchDepthMap[i][j] = 0;
        }
    }

    agent->currentSearchDepth = 1;
    agent->searchDepthMap[agent->curPosition.y][agent->curPosition.x] = agent->currentSearchDepth;
    agent->tracingBack = 0;
}

int checkTerminalCondition(Robot *robot, Agent *agent)
{
    // True if should terminate
    return agent->consecutiveTurns > 3 && isAtHome(robot) && robot->markers == 0;
}