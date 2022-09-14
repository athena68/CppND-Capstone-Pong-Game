#include "ball.h"

Ball::Ball(Vector2D position/*, Vector2D velocity*/, std::size_t w, std::size_t h, std::size_t screen_width, std::size_t screen_height)
    : _position(position), _screen_width(screen_width), _screen_height(screen_height)
    /*, _velocity(velocity)*/
{
    _render_info.x = position.x;
    _render_info.y = position.y;
    _render_info.w = w+5;
    _render_info.h = h+5;
    _velocity.x = ball_speed;
    _velocity.y = 0;
    printf("BALL::First ball pos(%d, %d), ball size (%d, %d)\n", _position.x, _position.y, _render_info.w, _render_info.h);
}
// static int s_count = 0;
void Ball::Update(Uint32 dTime)
{
    // ++s_count;
    _position += _velocity * dTime;
    // if (s_count < 10 ) printf("BALL::Update[%02d] ball pos(%d, %d), _velocity(%d, %d), dTime=%dms\n", s_count, _position.x, _position.y, _velocity.x, _velocity.y, dTime);
    _render_info.x = _position.x;
	_render_info.y = _position.y;
    // printf("BALL::Update render_info(%d, %d)\n", _render_info.x, _render_info.y);
}

void Ball::CollideWithPaddle(Contact const& contact)
{
    _position.x += contact.penetration;
    _velocity.x = -_velocity.x;

    if (contact.type == CollisionType::Top)
    {
        _velocity.y = -std::round(ball_speed * 3/4);
    }
    else if (contact.type == CollisionType::Bottom)
    {
        _velocity.y = std::round(ball_speed * 3/4);
    }
}

void Ball::CollideWithWall(Contact const& contact)
{
    if ((contact.type == CollisionType::Top)
        || (contact.type == CollisionType::Bottom))
    {
        _position.y += contact.penetration;
        _velocity.y = -_velocity.y;
    }
    else if (contact.type == CollisionType::Left)
    {
        _position.x = _screen_width / 2;
        _position.y = _screen_height / 2;
        _velocity.x = ball_speed;
        _velocity.y = std::round(ball_speed * 3/4);
    }
    else if (contact.type == CollisionType::Right)
    {
        _position.x = _screen_width / 2;
        _position.y = _screen_height / 2;
        _velocity.x = -ball_speed;
        _velocity.y = std::round(ball_speed * 3/4);
    }
}
