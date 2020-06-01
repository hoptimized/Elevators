#include "vector2.hpp"
#include <stdio.h>
#include <math.h>

//empty constructor
Vector2::Vector2() : x(0.f), y(0.f)
{
}

//parameterized constructor
Vector2::Vector2(float inX, float inY) : x(inX), y(inY)
{
}

//vector addition
Vector2 Vector2::operator+(const Vector2& v)
{
	Vector2 res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}

//vector subtraction
Vector2 Vector2::operator-(const Vector2& v)
{
	Vector2 res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}

//scalar multiplication
Vector2 Vector2::operator*(float s)
{
	Vector2 res;
	res.x = x * s;
	res.y = y * s;
	return res;
}

//scalar division
Vector2 Vector2::operator/(float s)
{
	Vector2 res;
	res.x = x / s;
	res.y = y / s;
	return res;
}

//normalize vecor
Vector2 Vector2::normalize()
{
	Vector2 res;
	res.x = x / length();
	res.y = y / length();
	return res;
}

//get length of vector
float Vector2::length()
{
	return (float)sqrt((double)x * (double)x + (double)y * (double)y);
}

//dot product
float Vector2::dot(const Vector2& v)
{
	return x * v.x + y * v.y;
}

//cross product
float Vector2::cross(const Vector2& v)
{
	return x * v.y - y * v.x;
}

//reflect vector at plane with given normal
Vector2 Vector2::reflect(const Vector2& n)
{
	Vector2 res = n;
	res = *this - (res.normalize() * 2.f * dot(res.normalize()));
	return res;
}
