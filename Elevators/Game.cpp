
#include "Renderer.hpp"
#include "World.hpp"
#include "Game.hpp"

#include "Elevator.hpp"
#include "ElevatorButton.hpp"
#include "SlowMoButton.hpp"


/*
 * CONSTRUCTOR
 *
 * Initializes the Game;
 * Generates UI buttons;
 * Generates Elevators;
 */
Game::Game() {

	/* UI Buttons */
	SlowMoButton0 = new SlowMoButton(375.f, 10.f, 0.f, "0.0x");
	SlowMoButton1 = new SlowMoButton(450.f, 10.f, 0.25f, "0.25x");
	SlowMoButton2 = new SlowMoButton(535.f, 10.f, 0.5f, "0.5x");
	SlowMoButton3 = new SlowMoButton(610.f, 10.f, 1.f, "1.0x");
	SlowMoButton4 = new SlowMoButton(685.f, 10.f, 2.f, "2.0x");
	World::Spawn(SlowMoButton0);
	World::Spawn(SlowMoButton1);
	World::Spawn(SlowMoButton2);
	World::Spawn(SlowMoButton3);
	World::Spawn(SlowMoButton4);

	/* Normal Elevator for the lower floors */
	Elevator* low1 = CreateElevator(50.f, 70.f, 20.f, 720.f, 380.f, {
		0.f,
		45.f,
		73.f,
		101.f,
		129.f,
		157.f,
		185.f,
		213.f,
		241.f,
		269.f,
		297.f,
		325.f,
		353.f
	});

	/* First normal Elevator for the higher floors */
	Elevator* high1 = CreateElevator(70.f, 70.f, 20.f, 720.f, 450.f, {
		0.f,
		45.f,
		381.f,
		409.f,
		437.f,
		465.f,
		493.f,
		521.f,
		549.f,
		577.f,
		605.f,
		633.f,
		661.f,
		689.f
	});

	/* Second normal Elevator for the higher floors */
	Elevator* high2 = CreateElevator(90.f, 70.f, 20.f, 720.f, 520.f, {
		0.f,
		45.f,
		381.f,
		409.f,
		437.f,
		465.f,
		493.f,
		521.f,
		549.f,
		577.f,
		605.f,
		633.f,
		661.f,
		689.f
	});

	/* High-speed Elevator for the observation deck */
	Elevator* panorama = CreateElevator(250.f, 28.f, 20.f, 717.f, 590.f, {
		0.f,
		685.f
	});
	panorama->GetMotor()->vmax = 150.f;
	panorama->GetMotor()->brakingDistance = 65.f;
}


/*
 * CreateElevator.
 * Helper function for creating an elevator with all its floors and buttons
*/
Elevator* Game::CreateElevator(float inX, float inY, float inW, float inH, float buttonsX, std::vector<float> positions)
{
	Elevator* elevator = new Elevator(inX, inY, inW, inH);

	//for each floor, generate and spawn all buttons, inform the elevator about the new floor
	for (unsigned int i = 0; i < positions.size(); ++i) {

		ElevatorButton* buttonDown = new ElevatorButton(buttonsX, inY + inH - positions[i] - 20.f, i, ElevatorButton::ButtonType::SummonDown);
		World::Spawn(buttonDown);

		ElevatorButton* buttonUp = new ElevatorButton(buttonsX + 15.f, inY + inH - positions[i] - 20.f, i, ElevatorButton::ButtonType::SummonUp);
		World::Spawn(buttonUp);

		ElevatorButton* buttonCabin = new ElevatorButton(buttonsX + 30.f, inY + inH - positions[i] - 20.f, i, ElevatorButton::ButtonType::Cabin);
		World::Spawn(buttonCabin);

		elevator->AddFloor(FloorInfo(positions[i], buttonUp, buttonDown, buttonCabin));
	}

	//Activate and spawn the elevator
	World::Spawn(elevator);

	return elevator;
}


/*
 * Update.
 * Nothing to do here. All handled by the actors.
 */
void Game::update(float timeStep, float mouseX, float mouseY, bool pressed) {
}


/*
 * RENDER.

 * Renders all static level content and UI:
 *   - soil
 *   - building floors
 *   - roof
 *   - floor labels
 *   - static ui labels
 *   - dividers
 *
 * NOTE:
 * There's a lot of redundancy in this function. In a next step, we could refine the class 
 * hierarchy and create a class for scene objects such as walls or entire building floors.
 * This way, the World object would take care of drawing all the scene objects and we could
 * create blueprints for building floors.
 */
void Game::render(Renderer& renderer)
{
	//soil
	renderer.drawRect(0.f, 745.f, 800.f, 55.f, 0x7F462C);

	//building floors
	renderer.drawRect(110.f,  70.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f,  98.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 126.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 154.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 182.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 210.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 238.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 266.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 294.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 322.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 350.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 378.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 406.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 434.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 462.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 490.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 518.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 546.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 574.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 602.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 630.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 658.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 686.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 714.f, 140.f, 3.f, 0xCCCCCC);
	renderer.drawRect(110.f, 742.f, 140.f, 3.f, 0xCCCCCC);

	//roof
	renderer.drawRect(50.f, 58.f, 200.f, 12.f, 0xCCCCCC);

	//floor labels
	renderer.drawText("Basement", 650, 765, 0xFFFFFF);
	renderer.drawText("Lobby", 650, 720, 0xFFFFFF);
	for (int i = 0; i < 23; ++i) {
		renderer.drawText(std::to_string(i + 2), 650, 692 - i * 28, 0xFFFFFF);
	}
	renderer.drawText("Observatory", 650, 35, 0xFFFFFF);

	//UI Labels
	renderer.drawText("Speed:", 300.f, 10.f, 0xFF0000);

	//dividers
	renderer.drawDivider(270, 780,  58, 0x444444, true);
	renderer.drawDivider(270, 780,  98, 0x444444, true);
	renderer.drawDivider(270, 780, 126, 0x444444, true);
	renderer.drawDivider(270, 780, 154, 0x444444, true);
	renderer.drawDivider(270, 780, 182, 0x444444, true);
	renderer.drawDivider(270, 780, 210, 0x444444, true);
	renderer.drawDivider(270, 780, 238, 0x444444, true);
	renderer.drawDivider(270, 780, 266, 0x444444, true);
	renderer.drawDivider(270, 780, 294, 0x444444, true);
	renderer.drawDivider(270, 780, 322, 0x444444, true);
	renderer.drawDivider(270, 780, 350, 0x444444, true);
	renderer.drawDivider(270, 780, 378, 0x444444, true);
	renderer.drawDivider(270, 780, 406, 0x444444, true);
	renderer.drawDivider(270, 780, 434, 0x444444, true);
	renderer.drawDivider(270, 780, 462, 0x444444, true);
	renderer.drawDivider(270, 780, 490, 0x444444, true);
	renderer.drawDivider(270, 780, 518, 0x444444, true);
	renderer.drawDivider(270, 780, 546, 0x444444, true);
	renderer.drawDivider(270, 780, 574, 0x444444, true);
	renderer.drawDivider(270, 780, 602, 0x444444, true);
	renderer.drawDivider(270, 780, 630, 0x444444, true);
	renderer.drawDivider(270, 780, 658, 0x444444, true);
	renderer.drawDivider(270, 780, 686, 0x444444, true);
	renderer.drawDivider(270, 780, 714, 0x444444, true);
}

