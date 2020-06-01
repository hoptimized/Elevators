
#include <iostream>
#include <algorithm>

#include "ElevatorMotor.hpp"
#include "ElevatorController.hpp"

 /** Default constructor */
ElevatorMotor::ElevatorMotor() : controller(nullptr), currentPos(0.f), lastPos(0.f), targetPos(0.f), startPos(0.f)
{
}


/* 
 * Tick
 * 
 * Lets the motor move one frame towards the target position.
 * May lock-in to the target position, if close enough.
 * Notifies controller about having arrived at the target position.
 * Picks its speed using vmin < speed < vmax, speed grows linear with distance to start position and target position
 *  --> smooth accelleration / deceleration
 *
 */
void ElevatorMotor::tick(float DeltaTime)
{
	if (std::abs(currentPos - targetPos) <= 1.f) {
		if (controller != nullptr && std::abs(lastPos - currentPos) > 0.01) controller->reachedPosition(currentPos);
		lastPos = currentPos;
		startPos = currentPos;
	}
	else {
		lastPos = currentPos;
		float closestDistance = std::min(std::abs(targetPos - currentPos), std::abs(startPos - currentPos));
		float speedFactor = std::min(closestDistance / brakingDistance, 1.f);
		float speed = std::max(speedFactor * vmax, vmin);
		currentPos += (targetPos > currentPos ? 1.f : -1.f) * speed * DeltaTime;
	}
}


/*
 * goToPosition.
 *
 * Called by the controller;
 * Sets a new target position.
 * Motor may ignore the command if it is moving too fast and too close to the desired target.
 *  --> avoids abrupt braking
 *
*/
void ElevatorMotor::goToPosition(float position)
{
	if (
		getCurrentDirection() == Direction::None
		|| (getCurrentDirection() == Direction::Up && currentPos < position - brakingDistance)
		|| (getCurrentDirection() == Direction::Down && currentPos > position + brakingDistance)
	) {
		targetPos = position;
	}
	
}


/* returns the current floor */
float ElevatorMotor::getCurrentPosition() const
{
	return currentPos;
}


/*
 * returns the current direction.
 * this function would make more sense if the elevator actually needed some time between floors.
 */
Direction ElevatorMotor::getCurrentDirection() const
{
	if (targetPos > currentPos + 1.f) {
		return Direction::Up;
	}
	else if (targetPos < currentPos - 1.f) {
		return Direction::Down;
	}
	else {
		return Direction::None;
	}
}
