#include "Cabin.hpp"

#include "renderer.hpp"

Cabin::Cabin(float inX, float inY, float inW, float inH, unsigned int inZIndex) : Actor(inX, inY, inW, inH, inZIndex)
{
}

void Cabin::update(float timeStep)
{
	__super::update(timeStep);
}

void Cabin::render(Renderer& renderer)
{
	__super::render(renderer);

	//fancy cabin design
	renderer.drawRect(position.x, position.y, w, h, 0x808080);
}
