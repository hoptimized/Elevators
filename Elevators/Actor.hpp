#pragma once

#include "Vector2.hpp"

class Renderer;
class Game;

class Actor {
public:

	//Constructor/Descructor
	Actor();
	Actor(float inX, float inY, float inW, float inH);
	Actor(float inX, float inY, float inW, float inH, unsigned int inZIndex);

protected:
	Vector2 velocity;
	Vector2 position;
	float w;
	float h;
	unsigned int zIndex = 0;
	bool bIsPendingKill;

public:

	//Standard functions
	virtual void update(float timeStep);
	virtual void render(Renderer& renderer);

	//GETTERS
	Vector2 getPosition() { return position; };
	Vector2 getCenter();
	float getWidth() { return w; };
	float getHeight() { return h; };
	Vector2 getVelocity() { return velocity; };
	virtual Vector2 getBoundingRectTopLeft();
	virtual Vector2 getBoundingRectBottomRight();
	unsigned int getRenderOrder() const { return zIndex; };

	//SETTERS
	void setPosition(const Vector2& v) { position = v; };
	void setWidth(float inW) { w = inW; };
	void setHeight(float inH) { h = inH; };

	//Collision
	bool CheckCollision(Actor* const otherActor, float timeStep);
	bool CheckCollision(Actor* const otherActor, float timeStep, Vector2& HitPoint, Vector2& outNormal, float& outRatio);
	
	//Mouse Events
	virtual void onClick();

	//Lifecycle Management
	virtual void Destroy() { bIsPendingKill = true; };
	bool IsPendingKill() const { return bIsPendingKill; };

};