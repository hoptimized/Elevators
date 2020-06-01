#include "renderer.hpp"
#include "World.hpp"
#include "Core.hpp"
#include "Game.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

/*
 * +++ CORE +++
 *
 * This file executes MAIN;
 * This file manages SDL and the window;
 * This file runs the EVENT LOOP;
 * This file bootstraps the GAME;
 * This file handles the WORLD
 *
 */

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	if (TTF_Init() < 0) printf("Error: %s \n", TTF_GetError());

	SDL_Window* pWindow = SDL_CreateWindow("Elevators",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			800, 800,
			0);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	Renderer renderer(pRenderer);

	TTF_Font* font = TTF_OpenFont("consolas.ttf", 20);
	renderer.SetFont(font);

	//LOAD GAMEMODE
	GameBase* pGame = new Game();

	float mouseX = 400;
	float mouseY = 400;
	bool mousePressed = false;

	bool running = true;
	unsigned int lastTime = SDL_GetTicks();
	while(running) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				break;
			case SDL_MOUSEMOTION:
				mouseX = (float)event.motion.x;
				mouseY = (float)event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mousePressed = true;
				break;
			case SDL_MOUSEBUTTONUP:
				mousePressed = false;
				break;
			}
		}

		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(pRenderer);

		unsigned int time = SDL_GetTicks();
		float timeStep = ((time - lastTime) / 1000.0f) * World::GetTimeScale();
		lastTime = time;

		pGame->update(timeStep, mouseX, mouseY, mousePressed);
		World::update(timeStep, mouseX, mouseY, mousePressed);

		pGame->render(renderer);
		World::render(renderer);

		SDL_RenderPresent(pRenderer);
	}

	delete pGame;

	SDL_Quit();
	return 0;
}