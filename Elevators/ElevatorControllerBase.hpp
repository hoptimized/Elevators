#pragma once

#include "ElevatorMotor.hpp"

class ElevatorControllerBase
{
public:
    virtual void summonButtonPushed(int summoningFloor, Direction direction) = 0;
    virtual void floorButtonPushed(int destinationFloor) = 0;
    virtual void reachedPosition(float position) = 0;
};