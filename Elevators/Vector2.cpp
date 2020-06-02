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
Vector2 Vector2::operator+(const Vector2& v) const
{
	Vector2 res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}
Vector2& Vector2::operator+=(const Vector2 & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

//vector subtraction
Vector2 Vector2::operator-(const Vector2& v) const
{
	Vector2 res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}
Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

//scalar multiplication
Vector2 Vector2::operator*(float s) const
{
	Vector2 res;
	res.x = x * s;
	res.y = y * s;
	return res;
}
Vector2& Vector2::operator*=(const float s)
{
	x *= s;
	y *= s;
	return *this;
}

//scalar division
Vector2 Vector2::operator/(float s) const
{
	Vector2 res;
	res.x = x / s;
	res.y = y / s;
	return res;
}
Vector2& Vector2::operator/=(const float s)
{
	x /= s;
	y /= s;
	return *this;
}

//normalize vecor
Vector2 Vector2::normalized() const
{
	float l = length();

	Vector2 res;
	res.x = x / l;
	res.y = y / l;
	return res;
}
Vector2& Vector2::normalize()
{
	float l = length();
	x /= l;
	y /= l;
	return *this;
}

//get length of vector
float Vector2::length() const
{
	return (float)sqrt((double)x * (double)x + (double)y * (double)y);
}

//dot product
float Vector2::dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

//cross product
float Vector2::cross(const Vector2& v) const
{
	return x * v.y - y * v.x;
}

//reflect vector at plane with given normal
Vector2 Vector2::reflected(const Vector2& n) const
{
	Vector2 normal = n.normalized();
	return *this - (normal * 2.f * this->dot(normal));
}
Vector2& Vector2::reflect(const Vector2& n)
{
	Vector2 normal = n.normalized();
	*this -= (normal * 2.f * this->dot(normal));
	return *this;
}
