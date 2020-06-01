#include <SDL.h>
#include <SDL_ttf.h>

#include "renderer.hpp"

Renderer::Renderer(SDL_Renderer* pRenderer) {
	m_pRenderer = pRenderer;
	font = nullptr;
}

Renderer::~Renderer()
{
	for (SDL_Texture* t : textures) {
		SDL_DestroyTexture(t);
	}
}

void Renderer::drawRect(int x, int y, int w, int h, int c) {
	SDL_SetRenderDrawColor( m_pRenderer, ( Uint8 )( ( c >> 16 ) & 255 ), ( Uint8 )( ( c >> 8 ) & 255 ), ( Uint8 )( c & 255), ( Uint8 )255 );
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderFillRect(m_pRenderer, &rect);
}

void Renderer::drawRect(float x, float y, float w, float h, int c)
{
	drawRect((int)x, (int)y, (int)w, (int)h, c);
}

SDL_Texture* Renderer::makeText(std::string inText, int c)
{
	if (font == nullptr) return nullptr;
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, inText.c_str(), { (Uint8)((c >> 16) & 255), (Uint8)((c >> 8) & 255), (Uint8)(c & 255), (Uint8)255 });
	SDL_Texture* text = SDL_CreateTextureFromSurface(m_pRenderer, textSurface);
	textures.insert(text);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	return text;
}

void Renderer::drawText(std::string inText, int x, int y, int c)
{
	if (font == nullptr) return;
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, inText.c_str(), { (Uint8)((c >> 16) & 255), (Uint8)((c >> 8) & 255), (Uint8)(c & 255), (Uint8)255 });
	SDL_Texture* text = SDL_CreateTextureFromSurface(m_pRenderer, textSurface);
	SDL_Rect textRect;
	textRect.x = x;
	textRect.y = y;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	SDL_RenderCopy(m_pRenderer, text, NULL, &textRect);
	SDL_DestroyTexture(text);
}

void Renderer::drawText(std::string inText, float x, float y, int c)
{
	drawText(inText, (int)x, (int)y, c);
}

void Renderer::drawText(SDL_Texture* t, int x, int y)
{
	SDL_Rect textRect;
	textRect.x = x;
	textRect.y = y;
	SDL_QueryTexture(t, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(m_pRenderer, t, NULL, &textRect);
}

void Renderer::drawText(SDL_Texture* t, float x, float y)
{
	drawText(t, (int)x, (int)y);
}

void Renderer::drawDivider(int x1, int x2, int y, int c, bool dashed)
{
	SDL_SetRenderDrawColor(m_pRenderer, (Uint8)((c >> 16) & 255), (Uint8)((c >> 8) & 255), (Uint8)(c & 255), (Uint8)255);
	if (!dashed) {
		SDL_RenderDrawLine(m_pRenderer, x1, y, x2, y);
	}
	else
	{
		//currently only supporting horizontal lines!
		for (int i = 0; i < x2 - x1 / 15 - 1; ++i) {
			SDL_RenderDrawLine(m_pRenderer, x1 + 15 * i, y, x1 + 15 * i + 5, y);
		}
	}
}

void Renderer::drawDivider(float x1, float x2, float y, int c, bool dashed)
{
	drawDivider((int)x1, (int)x2, (int)y, c, dashed);
}

void Renderer::drawArrowUp(int x, int y, int w, int c)
{
	SDL_SetRenderDrawColor(m_pRenderer, (Uint8)((c >> 16) & 255), (Uint8)((c >> 8) & 255), (Uint8)(c & 255), (Uint8)255);
	for (int i = 1; i <= w; ++i) {
		SDL_RenderDrawLine(m_pRenderer, x + (w - i) / 2, y + i - 1, x + w - (w - i) / 2, y + i - 1);
	}
}

void Renderer::drawArrowUp(float x, float y, float w, int c)
{
	drawArrowUp((int)x, (int)y, (int)w, c);
}

void Renderer::drawArrowDown(int x, int y, int w, int c)
{
	SDL_SetRenderDrawColor(m_pRenderer, (Uint8)((c >> 16) & 255), (Uint8)((c >> 8) & 255), (Uint8)(c & 255), (Uint8)255);
	for (int i = 1; i <= w; ++i) {
		SDL_RenderDrawLine(m_pRenderer, x + (w - i) / 2, y + w - i, x + w - (w - i) / 2, y + w - i);
	}
}

void Renderer::drawArrowDown(float x, float y, float w, int c)
{
	drawArrowDown((int)x, (int)y, (int)w, c);
}

