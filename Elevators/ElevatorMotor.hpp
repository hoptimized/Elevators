#pragma once

class ElevatorControllerBase;

enum Direction { Up = 1, None = 0, Down = -1 };

class ElevatorMotor
{
public:
    float vmax = 80.f;
    float vmin = 5.f;
    float brakingDistance = 25.f;

protected:
    ElevatorControllerBase* controller;
    float currentPos;
    float startPos;
    float targetPos;
    float lastPos;

public:
    ElevatorMotor();
    void setController(ElevatorControllerBase* _controller) { controller = _controller; };

    void tick(float DeltaTime);

    void goToPosition(float position);
    float getCurrentPosition() const;
    Direction getCurrentDirection() const;
};