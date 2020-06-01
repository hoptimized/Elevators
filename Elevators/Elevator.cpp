
#include "Renderer.hpp"
#include "World.hpp"

#include "Elevator.hpp"
#include "Cabin.hpp"
#include "ElevatorButton.hpp"


/* Default Constructor */
Elevator::Elevator() : Elevator(0.f, 0.f, 0.f, 0.f)
{
}


/*
 * Parameterized Constructor.
 *
 * Initializes values;
 * Links motor and controller with each other;
 * Creates the cabin;
 */
Elevator::Elevator(float inX, float inY, float inW, float inH) : Actor(inX, inY, inW, inH)
{
	motor.setController(&controller);
	controller.setMotor(&motor);

    //create Cabin with a z-index greater than the elevator --> draw cabin on top of elevator shaft
	cabin = new Cabin(0.f, 0.f, w - 3.f * WALL_THICKNESS, CABIN_HEIGHT, zIndex + 1);
	World::Spawn(cabin);
}

/* Destructor */
Elevator::~Elevator()
{
    cabin->Destroy();
}


/*
 * Update.
 *
 * Ticks components;
 * Synchronizes position of cabin and motor.
 */
void Elevator::update(float timeStep)
{
	__super::update(timeStep);

	controller.tick(timeStep);
	motor.tick(timeStep);

	cabin->setPosition({position.x + 1.5f * WALL_THICKNESS, position.y + h - CABIN_HEIGHT - 1.5f * WALL_THICKNESS - motor.getCurrentPosition()});
}


/*
 * Render.
 *
 * Draws the elevator shaft.
 * Note: the cabin is an Actor and will be rendered by the World
 */
void Elevator::render(Renderer& renderer)
{
	__super::render(renderer);

	renderer.drawRect(position.x, position.y, w, h, 0xFFFFFF);
	renderer.drawRect(position.x + WALL_THICKNESS, position.y + WALL_THICKNESS, w - 2.f * WALL_THICKNESS, h - 2.f * WALL_THICKNESS, 0x000000);
}


/*
 * AddFloor.
 *
 * Adds a new floor to the elevator.
 * Registers the new floor (stop position and buttons) with the controller
 * Makes the buttons aware of the controller --> gives buttons a way to fire event callbacks
 */
void Elevator::AddFloor(const FloorInfo& info)
{
	controller.connectFloor(info);
	info.CabinButton->SetController(&controller);
	info.SummonDownButton->SetController(&controller);
	info.SummonUpButton->SetController(&controller);
}