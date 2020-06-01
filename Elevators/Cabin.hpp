#include "actor.hpp"

class Cabin : public Actor {
public:
	Cabin(float inX, float inY, float inW, float inH, unsigned int zIndex);
	void update(float timeStep);
	void render(Renderer& renderer);
};