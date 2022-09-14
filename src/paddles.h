#ifndef PADDLES_H
#define PADDLES_H

#include "vector2d.h"
#include <SDL2/SDL.h>

class Paddle
{
public:
	enum class Direction { kUp = -1, kDown = 1, kOnHold = 0 };

	Paddle(Vector2D position, std::size_t paddle_w, std::size_t paddle_h,
		   std::size_t scr_h, Vector2D velocity);
	void Update(Uint32 dTime);
	void ChangeDirection(Direction input);

	Vector2D _position;
	SDL_Rect _render_info{};
	Vector2D _velocity;
	std::size_t _screen_height;
	const int paddle_speed = 20;//TODO : support change this speed
};

#endif //PADDLES_H