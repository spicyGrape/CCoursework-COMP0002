#include "Agent.h"

void operateRobot()
{
    // Forward
    if (canMoveForward())
    {
        forward();
    }
    // Left
    else
    {
        left();
    }
    return;
}