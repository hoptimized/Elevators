#include <limits>

#include "ElevatorController.hpp"
#include "ElevatorMotor.hpp"
#include "ElevatorButton.hpp"

/* Default constructor */
ElevatorController::ElevatorController() : currentRoute(Direction::None), currentFloor(0), motor(nullptr)
{
}

/* 
 * Destructor.
 * Deletes all buttons.
 */
ElevatorController::~ElevatorController()
{
	for (FloorInfo& floor : floors) {
		floor.CabinButton->Destroy();
		floor.SummonDownButton->Destroy();
		floor.SummonUpButton->Destroy();
	}
}


/*
 * connectFloor.
 * Copies the floor info into the controller
 */
void ElevatorController::connectFloor(const FloorInfo& info)
{
	floors.push_back(info);
}


/*
 * Tick.
 * If the elevator is currently (un)loading PAX, finish loading or tick the timer to continue loading
 */
void ElevatorController::tick(float DeltaTime)
{
	if (loading) {
		if (loadingTimer > loadingDuration) {
			loading = false;
			selectNextFloor();
		}
		else {
			loadingTimer += DeltaTime;
		}
	}
}


/*
 * Load.
 *
 * This refers to the (UN-)LOADING OF PAX!
 * Resets the loading timer and activates loading mode
 *
 */
void ElevatorController::load()
{
	if (loading) return;

	loading = true;
	loadingTimer = 0.f;
}


/*
 * summonButtonPushed.
 * 
 * Called when someone summons the elevator.
 * Flags the desired button (up/down) on the summoning floor as pushed.
 * Triggers the controller to re-assess the current target floor.
 */
void ElevatorController::summonButtonPushed(int summoningFloor, Direction direction)
{
	if (direction == Direction::Up) {
		floors[summoningFloor].SummonUpButton->SetIsActivated(true);
	}
	else if (direction == Direction::Down) {
		floors[summoningFloor].SummonDownButton->SetIsActivated(true);
	}

	selectNextFloor();
}


/*
 * floorButtonPushed.
 *
 * Called when someone inside the elevator pushs a button.
 * Flags the button for the desired floor as pushed.
 * Triggers the controller to re-assess the current target floor.
 */
void ElevatorController::floorButtonPushed(int destinationFloor)
{
	floors[destinationFloor].CabinButton->SetIsActivated(true);
	selectNextFloor();
}


/*
 * reachedFloor.
 *
 * Called by the motor when the elevator arrives on a floor.
 * Turns off all related buttons if the elevator has just been moving (enroute).
 */
void ElevatorController::reachedPosition(float position)
{
	int oldFloor = currentFloor;
	updateCurrentFloor(position);

	if (oldFloor != currentFloor) {
		floors[currentFloor].CabinButton->SetIsActivated(false);
		
		if (currentRoute == Direction::Up || currentRoute == Direction::None)
			floors[currentFloor].SummonUpButton->SetIsActivated(false);
		if (currentRoute == Direction::Down || currentRoute == Direction::None)
			floors[currentFloor].SummonDownButton->SetIsActivated(false);

		load();
	}
}


/*
 * updateCurrentFloor.
 * find the current floor number from a given stop position
 */
void ElevatorController::updateCurrentFloor(float yPos)
{
	int i = 0;
	for (const FloorInfo& floor : floors) {
		if (std::abs(floor.yPos - yPos) < 10.f) {
			currentFloor = i;
			return;
		}
		++i;
	}
}


/*
 * selectNextFloor.
 *
 * Re-assesses the floor the elevator should currently head to.
 * Calls findNextFloor() to identify the target floor.
 * Updates currentRoute (none/up/down) according to the new target.
 * Instructs the motor to move to the target floor.
 */
void ElevatorController::selectNextFloor()
{
	if (motor == nullptr) return;

	int oldFloor = currentFloor;

	unsigned int target = findNextFloor();
	if (target == currentFloor) {
		currentRoute = Direction::None;
		floors[oldFloor].SummonDownButton->SetIsActivated(false);
		floors[oldFloor].SummonUpButton->SetIsActivated(false);
	}
	else {
		if (bHasReversed) {
			if (currentRoute == Direction::Down)
				floors[oldFloor].SummonDownButton->SetIsActivated(false);
			else if (currentRoute == Direction::Up)
				floors[oldFloor].SummonUpButton->SetIsActivated(false);
		}

		currentRoute = target > currentFloor ? Direction::Up : Direction::Down;
		motor->goToPosition(floors[target].yPos);
	}
	
	bHasReversed = false;
}


/**
 * findNextFloor.
 *
 * Internal helper function for finding the next floor to go to.
 * May call itself recursively ONCE. Depth of recursion is controlled by the boolean parameter.
 * 
 * Algorithm:
 *  1. If elevator is currently en-route up or down the building:
 *    1a. Check floorButtons and the summonButtons that are on the way. Pick the closest of these buttons. If a target has been found, return the target. Else, continue execution.
          Example:
		  If we are currently on floor 4 and we are traveling up, check floors 5 through 9 and return the closest floor that
          is a target (floorButton is pushed) or that has someone waiting outside (summonButton pushed) who wants to go up.
		  This way we will stop for floors 'on the way', if requested.
      1b. Check summonButtons that are on the route but want to travel in the opposite direction. Pick the furthest of these buttons. If a target has been found, return the target. Else, continue execution.
	      Example:
		  If we are currently on floor 4 and we are traveling up (and no one wants to go to floors 5-9; and no one on floors 5-9 summoned the elevator for going up),
		  check floors 9 through 5 and return the first floor that has someone waiting outside who wants to go down.
		  Note:
		  The purpose of this move is to find the best possible location for reversing and traveling in the opposite direction.
	  1c. If we are in a recursive call (=if we have just checked the other direction), return. The elevator will now idle.
	  1d. Change direction and recursively check the new direction.
	2. If elevator is currently idling:
	  2a. Browse through all buttons and go to the first button that is turned on.
	      Explanation: if the elevator has been idling, there should only be one button pressed at maximum. Immediately go to that button.
 */
unsigned int ElevatorController::findNextFloor(bool changedDirection)
{
	if (changedDirection) bHasReversed = true;

	unsigned int i = 0;
	unsigned int target = currentFloor;

	if (currentRoute != Direction::None) {

		/** Check buttons on the way */
		i = currentFloor + currentRoute;
		while (i >= 0 && i < floors.size()) {
			if (floors[i].CabinButton->GetIsActivated() || (currentRoute == Direction::Up && floors[i].SummonUpButton->GetIsActivated()) || (currentRoute == Direction::Down && floors[i].SummonDownButton->GetIsActivated())) {
				target = i;
				break;
			}
			i += currentRoute;
		}
		if (target != currentFloor) return target;


		/** Check buttons en-route for the opposite direction */
		i = currentRoute == Direction::Up ? (floors.size() - 1) : 0;
		while (i >= 0 && i < floors.size() && i != currentFloor) {
			if ((currentRoute == Direction::Up && floors[i].SummonDownButton->GetIsActivated()) || (currentRoute == Direction::Down && floors[i].SummonUpButton->GetIsActivated())) {
				target = i;
				break;
			}
			i += -currentRoute;
		}
		if (target != currentFloor) return target;


		/**	Check if we should idle */
		if (changedDirection) return target;


		/** Check the other direction */
		currentRoute = currentRoute == Direction::Up ? Direction::Down : Direction::Up;
		return findNextFloor(true);

	}
	else {


		/** Elevator has been idling, find a floor to go to */
		for (i = 0; i < floors.size(); ++i) {
			if (i == currentFloor) continue;
			if (floors[i].CabinButton->GetIsActivated() || floors[i].SummonDownButton->GetIsActivated() || floors[i].SummonUpButton->GetIsActivated()) return i;
		}

	}

	return currentFloor;
}

