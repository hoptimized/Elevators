#pragma once

#include "actor.hpp"

class SlowMoButton : public Actor {
public:
	SlowMoButton(float inX, float inY, float inSpeed, const std::string& inCaption);

	void render(Renderer& renderer) override;
	void onClick() override;

private:
	float speed;
	std::string caption;
};