#include "vector2d.h"

Vector2D Vector2D::operator+(Vector2D const& rhs)
{
    return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D& Vector2D::operator+=(Vector2D const& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

Vector2D Vector2D::operator*(int rhs)
{
    return Vector2D(x * rhs, y * rhs);
}