#pragma once

#include "actor.hpp"

class ElevatorController;

class ElevatorButton : public Actor {
public:
	enum ButtonType {
		SummonUp = 1,
		SummonDown = -1,
		Cabin = 0
	};

	ElevatorButton(float inX, float inY, int inFloor, ButtonType inType);

	void update(float timeStep) override;
	void render(Renderer& renderer) override;
	void onClick() override;

	void SetController(ElevatorController* _controller);
	void SetIsActivated(bool _bIsActivated) { bIsActivated = _bIsActivated; };
	bool GetIsActivated() const { return bIsActivated; };

private:
	bool bIsActivated = false;
	unsigned int floor;
	ButtonType buttonType;
	ElevatorController* controller;
};