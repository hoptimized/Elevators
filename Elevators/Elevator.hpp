#pragma once

#include "Actor.hpp"
#include "ElevatorController.hpp"
#include "ElevatorMotor.hpp"

class Cabin;

class Elevator : public Actor {
public:
	Elevator();
	Elevator(float inX, float inY, float inW, float inH);
	~Elevator();

	void update(float timeStep) override;
	void render(Renderer& renderer) override;

	/* Adds a new floor with all buttons */
	void AddFloor(const FloorInfo& info);

	//GETTERS
	ElevatorMotor* GetMotor() { return &motor; };

private:

	const float WALL_THICKNESS = 2.f;
	const float CABIN_HEIGHT = 25.f;

	/* Child Actors */
	Cabin* cabin;

	/* Components */
	ElevatorController controller;
	ElevatorMotor motor;

};