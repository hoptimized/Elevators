#include "renderer.hpp"
#include "World.hpp"

#include "SlowMoButton.hpp"

SlowMoButton::SlowMoButton(float inX, float inY, float inSpeed, const std::string& inCaption) : Actor(inX, inY, 10.f, 10.f), speed(inSpeed), caption(inCaption)
{
}

void SlowMoButton::render(Renderer& renderer)
{
	renderer.drawRect(position.x, position.y + 4.f, w, h, 0xFF0000);
	renderer.drawText(caption, position.x + w + 3, position.y, 0xFF0000);
}

void SlowMoButton::onClick()
{
	World::SetTimeScale(speed);
}
