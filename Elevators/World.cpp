#include "World.hpp"
#include "Actor.hpp"

/* Set of all spawned Actors */
std::unordered_set<Actor*> World::actors;

/* Actors arranged by render order */
std::multimap<int, Actor*> World::renderOrder;

/* Simulation speed, 1.f = 100% */
float World::timeScale = 1.f;


/*
 * Spawn.
 * Registers an actor with the world.
 * Activates ticking and rendering.
 */
void World::Spawn(Actor* actor)
{
	actors.emplace(actor);
	renderOrder.insert({ actor->getRenderOrder(), actor });
}


/*
 * IsValid.
 *
 * Checks if a pointer refers to a valid actor.
 *
 * Criteria:
 *   - pointer is NOT NULL
 *   - actor is registered with the world
 *   - actor is not pending kill
 */
bool World::IsValid(Actor* actor)
{
	return actor != nullptr && actors.find(actor) != actors.end() && !actor->IsPendingKill();
}


/*
 * Update.
 * Ticks all actors, processes click events and destroys actors
 */
void World::update(float timeStep, float mouseX, float mouseY, bool pressed)
{
	/* Update Actors and process Click Events */
	for (Actor* actor : actors)
	{
		if (pressed) {
			//TODO: this code does NOT belong here. Refactor!
			if (mouseX > actor->getBoundingRectTopLeft().x && mouseX < actor->getBoundingRectBottomRight().x && mouseY > actor->getBoundingRectTopLeft().y && mouseY < actor->getBoundingRectBottomRight().y) actor->onClick();
		}

		actor->update(timeStep);
	}

	/* Remove actors that have been Destroy()ed */
	for (Actor* actor : actors)
	{
		if (actor->IsPendingKill()) {
			actors.erase(actor);
			delete actor;
		}
	}
}


/*
 * Render.
 * Renders actors in the correct order
 */
void World::render(Renderer& renderer)
{
	std::multimap<int, Actor*>::iterator it;
	for (it = renderOrder.begin(); it != renderOrder.end(); ++it) {
		if (World::IsValid(it->second)) {
			it->second->render(renderer);
		}
		else {
			renderOrder.erase(it);
		}
	}
}
