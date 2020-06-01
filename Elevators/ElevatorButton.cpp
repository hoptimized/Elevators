#include "ElevatorButton.hpp"

#include "renderer.hpp"
#include "ElevatorController.hpp"

ElevatorButton::ElevatorButton(float inX, float inY, int inFloor, ButtonType inType) : Actor(inX, inY, 10.f, 10.f), floor(inFloor), buttonType(inType), controller(nullptr)
{
}

void ElevatorButton::update(float timeStep)
{
}

void ElevatorButton::render(Renderer& renderer)
{
	int c = bIsActivated ? 0xffff00 : 0xFFFFFF;

	switch (buttonType) {
	case ElevatorButton::ButtonType::Cabin:
		renderer.drawRect(position.x, position.y, w, h, c);
		break;
	case ElevatorButton::ButtonType::SummonDown:
		renderer.drawArrowDown(position.x, position.y, w, c);
		break;
	case ElevatorButton::ButtonType::SummonUp:
		renderer.drawArrowUp(position.x, position.y, w, c);
		break;
	}
}

void ElevatorButton::onClick()
{
	__super::onClick();

	if (controller == nullptr) return;

	switch (buttonType) {
	case ElevatorButton::ButtonType::Cabin:
		controller->floorButtonPushed(floor);
		break;
	case ElevatorButton::ButtonType::SummonDown:
		controller->summonButtonPushed(floor, Direction::Down);
		break;
	case ElevatorButton::ButtonType::SummonUp:
		controller->summonButtonPushed(floor, Direction::Up);
		break;
	}
}

void ElevatorButton::SetController(ElevatorController* _controller)
{
	controller = _controller;
}

