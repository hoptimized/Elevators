#pragma once

#include <string>
#include <set>

struct SDL_Renderer;
struct _TTF_Font;
struct SDL_Texture;

class Renderer {
public:
	Renderer(SDL_Renderer* pRenderer);
	~Renderer();

	void SetFont(_TTF_Font* inFont) { font = inFont; };

	void drawRect(int x, int y, int w, int h, int c);
	void drawRect(float x, float y, float w, float h, int c);

	void drawDivider(int x1, int x2, int y, int c, bool dashed = false);
	void drawDivider(float x1, float x2, float y, int c, bool dashed = false);

	void drawArrowUp(int x, int y, int w, int c);
	void drawArrowUp(float x, float y, float w, int c);

	void drawArrowDown(int x, int y, int w, int c);
	void drawArrowDown(float x, float y, float w, int c);


	SDL_Texture* makeText(std::string inText, int c);

	void drawText(std::string inText, int x, int y, int c);
	void drawText(std::string inText, float x, float y, int c);
	void drawText(SDL_Texture* t, int x, int y);
	void drawText(SDL_Texture* t, float x, float y);

private:
	SDL_Renderer* m_pRenderer;
	_TTF_Font* font;
	std::set<SDL_Texture*> textures;
};