#ifndef VECTOR_2D_H
#define VECTOR_2D_H

class Vector2D
{
public:
	Vector2D(): x(0.0f), y(0.0f)
	{}

	Vector2D(int _x, int _y) : x(_x), y(_y)
	{}

	Vector2D operator+(Vector2D const& rhs);
	Vector2D& operator+=(Vector2D const& rhs);
	Vector2D operator*(int rhs);

	int x;
	int y;
};

#endif //VECTOR_2D_H