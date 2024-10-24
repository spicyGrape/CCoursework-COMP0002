#include "Agent.h"

void operateRobot(Robot *robot)
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