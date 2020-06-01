#pragma once

#include <vector>

#include "Core.hpp"

class Elevator;
class SlowMoButton;

class Game : public GameBase {
public:
	Game();
	void update(float timeStep, float mouseX, float mouseY, bool pressed);
	void render(Renderer& renderer);
protected:

	/* Helps to generate an elevator with all its floors and buttons */
	Elevator* CreateElevator(float inX, float inY, float inW, float inH, float buttonsX, std::vector<float> positions);

	/* The UI Buttons for controlling the simulation speed */
	SlowMoButton* SlowMoButton0;
	SlowMoButton* SlowMoButton1;
	SlowMoButton* SlowMoButton2;
	SlowMoButton* SlowMoButton3;
	SlowMoButton* SlowMoButton4;
};