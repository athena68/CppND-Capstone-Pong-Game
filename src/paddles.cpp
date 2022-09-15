#include "paddles.h"

Paddle::Paddle(Vector2D position, std::size_t w, std::size_t h,
               std::size_t scr_h, Vector2D velocity)
    : _position(position)
    , _velocity(velocity)
{
    _render_info.x = position.x;
    _render_info.y = position.y;
    _render_info.w = w;
    _render_info.h = h;
    _screen_height = scr_h;
    // printf("BALL::First paddle pos(%d, %d), paddle size (%d, %d)\n", _position.x, _position.y, _render_info.w, _render_info.h);

}

void Paddle::Update(Uint32 dTime)
{
    _position += _velocity * dTime;

    if (_position.y < 0) {
        // Restrict to top of the screen
        _position.y = 0;
    }
    else if (_position.y > (_screen_height - _render_info.h))
    {
        // Restrict to bottom of the screen
        _position.y = _screen_height - _render_info.h;
    }

    _render_info.y = _position.y;
}


void Paddle::ChangeDirection(Paddle::Direction input)
{
    switch(input) {
        case Paddle::Direction::kDown:
            _velocity.y = paddle_speed;          
            break;
        case Paddle::Direction::kUp:
            _velocity.y = -paddle_speed;
            break;
        case Paddle::Direction::kOnHold:
            _velocity.y = 0;
            break;                        
    }
}