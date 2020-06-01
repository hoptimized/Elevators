#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2 {

public:
    Vector2();
    Vector2(float inX, float inY);

protected:


public:
    float x, y;

    Vector2 operator+(const Vector2& v);
    Vector2 operator-(const Vector2& v);
    Vector2 operator*(const float s);
    Vector2 operator/(const float s);

    Vector2 normalize();
    float length();

    float dot(const Vector2& v);
    float cross(const Vector2& v);

    Vector2 reflect(const Vector2& n);
};

#endif