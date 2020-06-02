#pragma once

class Vector2
{
public:
    Vector2();
    Vector2(float inX, float inY);

protected:


public:
    float x, y;

    Vector2 operator+(const Vector2& v) const;
    Vector2& operator+=(const Vector2 & v);
    Vector2 operator-(const Vector2& v) const;
    Vector2& operator-=(const Vector2& v);
    Vector2 operator*(const float s) const;
    Vector2& operator*=(const float s);
    Vector2 operator/(const float s) const;
    Vector2& operator/=(const float s);

    Vector2 normalized() const;
    Vector2& normalize();

    float length() const;

    float dot(const Vector2& v) const;
    float cross(const Vector2& v) const;

    Vector2 reflected(const Vector2& n) const;
    Vector2& reflect(const Vector2& n);
};

//cummutative operator for multiplication
static Vector2 operator*(float a, const Vector2& v) { return v * a; }