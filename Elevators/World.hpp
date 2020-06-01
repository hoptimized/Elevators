#pragma once

#include <map>
#include <unordered_set>

class Actor;
class Renderer;

class World {
private:
	static std::unordered_set<Actor*> actors;
	static std::multimap<int, Actor*> renderOrder;
	static float timeScale;

public:
	static void Spawn(Actor* actor);
	static bool IsValid(Actor* actor);

	static void update(float timeStep, float mouseX, float mouseY, bool pressed);
	static void render(Renderer& renderer);

	static void SetTimeScale(float inScale) { timeScale = inScale; };
	static float GetTimeScale() { return timeScale; };
};