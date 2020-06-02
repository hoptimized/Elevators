#include <algorithm>
#include <limits>

#include "Game.hpp"
#include "Actor.hpp"

//Default Constructor
Actor::Actor()
	: Actor(0.f, 0.f, 0.f, 0.f, 0)
{
}

//Parameterized Constructor
Actor::Actor(float inX, float inY, float inW, float inH)
	: Actor(inX, inY, inW, inH, 0)
{
}

//Parameterized Constructor
Actor::Actor(float inX, float inY, float inW, float inH, unsigned int inZIndex)
	: position({ inX, inY }), velocity({ 0.f, 0.f }), w(inW), h(inH), bIsPendingKill(false), zIndex(inZIndex)
{
}

void Actor::update(float timeStep)
{
	//default behavior can be added here
}

void Actor::render(Renderer& renderer)
{
	//default behavior can be added here
}

//Returns the center of the actor
Vector2 Actor::getCenter() const
{
	return Vector2(position.x + w / 2, position.y + h / 2);
}

//Returns the top left corner of the collision box
Vector2 Actor::getBoundingRectTopLeft() const
{
	return position;
}

//Returns the bottom right corner of the collision box
Vector2 Actor::getBoundingRectBottomRight() const
{
	return Vector2(position.x + w, position.y + h);
}


//Simple collision check, returns true (colliding) or false (not colliding)
bool Actor::CheckCollision(Actor* const otherActor, float timeStep) const
{
	Vector2 ignoreHitPoint;
	Vector2 ignoreNormal;
	float ignoreRatio;
	return CheckCollision(otherActor, timeStep, ignoreHitPoint, ignoreNormal, ignoreRatio);
}


//Full collision check, returns true/false plus location of hit, normal of hit surface, sweeping ratio
bool Actor::CheckCollision(Actor* const otherActor, float timeStep, Vector2& HitPoint, Vector2& outNormal, float& outRatio) const
{

	//scale the velocity according to the current timeStep
	Vector2 scaledVelocity = timeStep * velocity;

	//Quick proximity check, saves performance
	if ((getCenter() - otherActor->getCenter()).length() > (scaledVelocity.length() + std::max(w, h)/2 + std::max(otherActor->getWidth(), otherActor->getHeight()) / 2) * 1.1f) return false;

	//Swept AABB collision adapted from https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (scaledVelocity.x > 0.0f)
	{
		xInvEntry = otherActor->getBoundingRectTopLeft().x - getBoundingRectBottomRight().x;
		xInvExit = otherActor->getBoundingRectBottomRight().x - getBoundingRectTopLeft().x;
	}
	else
	{
		xInvEntry = otherActor->getBoundingRectBottomRight().x - getBoundingRectTopLeft().x;
		xInvExit = otherActor->getBoundingRectTopLeft().x - getBoundingRectBottomRight().x;
	}

	if (scaledVelocity.y > 0.0f)
	{
		yInvEntry = otherActor->getBoundingRectTopLeft().y - getBoundingRectBottomRight().y;
		yInvExit = otherActor->getBoundingRectBottomRight().y - getBoundingRectTopLeft().y;
	}
	else
	{
		yInvEntry = otherActor->getBoundingRectBottomRight().y - getBoundingRectTopLeft().y;
		yInvExit = otherActor->getBoundingRectTopLeft().y - getBoundingRectBottomRight().y;
	}

	float xEntry, yEntry;
	float xExit, yExit;

	if (scaledVelocity.x == 0.0f)
	{
		xEntry = FLT_MIN;
		xExit = FLT_MAX;
	}
	else
	{
		xEntry = xInvEntry / scaledVelocity.x;
		xExit = xInvExit / scaledVelocity.x;
	}

	if (scaledVelocity.y == 0.0f)
	{
		yEntry = FLT_MIN;
		yExit = FLT_MAX;
	}
	else
	{
		yEntry = yInvEntry / scaledVelocity.y;
		yExit = yInvExit / scaledVelocity.y;
	}

	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	//check if collision has occured
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) return false;

	//save the sweeping ratio (0 < r < 1) example: collision occured 60% into the last frame: r=0.6
	outRatio = entryTime;

	//save the collision normal. useful for deflection
	if (xEntry > yEntry)
	{
		if (xInvEntry < 0.0f)
		{
			outNormal = Vector2(1.f, 0.f);
		}
		else
		{
			outNormal = Vector2(-1.f, 0.f);
		}
	}
	else
	{
		if (yInvEntry < 0.0f)
		{
			outNormal = Vector2(0.f, 1.f);
		}
		else
		{
			outNormal = Vector2(0.f, -1.f);
		}
	}

	//save the hit point, useful for determining the pricese point of impact on the racket
	HitPoint.x = position.x - velocity.x * timeStep * (1.f - entryTime);
	HitPoint.y = position.y - velocity.y * timeStep * (1.f - entryTime);

	return true;
}


void Actor::onClick()
{
	//Default behavior can be added here
}
