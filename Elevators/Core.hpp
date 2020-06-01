#pragma once

class Renderer;

class GameBase {
public:
	virtual ~GameBase() {}

	//called every frame to update everything
	virtual void update(float timeStep, float mouseX, float mouseY, bool pressed) = 0;

	//called every frame to draw everything
	virtual void render(Renderer& renderer) = 0;
};