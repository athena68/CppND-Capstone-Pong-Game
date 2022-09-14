#ifndef BALL_H
#define BALL_H

#include "vector2d.h"
#include <SDL2/SDL.h>

class Ball
{
public:
	const int ball_speed = 20; //TODO : support change ball speed dynamically
	enum class CollisionType { None, Top, Middle, Bottom, Left, Right };
	struct Contact {
		CollisionType type;
		int penetration;
	};

	Ball(Vector2D position/*, Vector2D velocity*/, std::size_t w, std::size_t h, 
		std::size_t screen_width, std::size_t screen_height);

	void Update(Uint32 dTime);
	void CollideWithPaddle(Contact const& contact);
	void CollideWithWall(Contact const& contact);

	SDL_Rect _render_info{};
	Vector2D _position;
	Vector2D _velocity;
	std::size_t _screen_width;
	std::size_t _screen_height;	
};

#endif //BALL_H