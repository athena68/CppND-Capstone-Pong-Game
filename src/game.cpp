#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>

Game::Game(std::size_t screen_width, std::size_t screen_height,
           std::size_t grid_width, std::size_t grid_height)
           : _screen_width(screen_width), _screen_height(screen_height)
{
  //Create ball
  int ball_width = screen_width / grid_width;
  int ball_height = screen_height / grid_height;
  Vector2D ball_pos = Vector2D((screen_width / 2.0f) - (screen_width / grid_width / 2.0f),
                               (screen_height / 2.0f) - (screen_height / grid_height / 2.0f));
  ball = std::make_unique<Ball>(ball_pos, ball_width, ball_height, screen_width, screen_height);

  //Create paddles
  int paddle_width = screen_width / grid_width;
  int paddle_height = screen_height / grid_height * 10;
  Vector2D paddle_one_pos = Vector2D(50.0f, (screen_height / 2.0f) - (paddle_height / 2.0f)); 
  Vector2D paddle_two_pos = Vector2D(screen_width - 50.0f, (screen_height / 2.0f) - (paddle_height / 2.0f)); 
  paddle_one = std::make_unique<Paddle>(paddle_one_pos, paddle_width, paddle_height, screen_height, Vector2D(0.0f, 0.0f));
  paddle_two = std::make_unique<Paddle>(paddle_two_pos, paddle_width, paddle_height, screen_height, Vector2D(0.0f, 0.0f));
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start = 0;
  Uint32 frame_end = 0;
  Uint32 frame_duration = 0;
  int n_player_one_score = 0;
  int n_player_two_score = 0;

  //Create player score manager
  
  player_one_score = std::make_unique<PlayerScore>(Vector2D(_screen_width / 4, 20), renderer.GetRenderer());
  player_two_score = std::make_unique<PlayerScore>(Vector2D(3 * _screen_width / 4, 20), renderer.GetRenderer());

  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, *paddle_one, *paddle_two);
    Update(frame_duration, n_player_one_score, n_player_two_score);
    renderer.Render(*ball, *paddle_one, *paddle_two, *player_one_score, *player_two_score);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_duration = frame_end - frame_start;


    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update(Uint32 dTime, int &iPlayerOneScore, int &iPlayerTwoScore)
{
  // printf("Frame duration : %d\n", dTime);
  paddle_one->Update(dTime);
  paddle_two->Update(dTime);

  ball->Update(dTime);

  // Check collisions
  Ball::Contact contact_paddle_one = CheckPaddleCollision(*ball, *paddle_one);
  Ball::Contact contact_paddle_two = CheckPaddleCollision(*ball, *paddle_two);
  Ball::Contact contact_wall       = CheckWallCollision(*ball);
  if (contact_paddle_one.type != Ball::CollisionType::None)
  {
    ball->CollideWithPaddle(contact_paddle_one);
  }
  else if (contact_paddle_two.type != Ball::CollisionType::None)
  {
    ball->CollideWithPaddle(contact_paddle_two);
  }
  else if (contact_wall.type != Ball::CollisionType::None)
  {
    ball->CollideWithWall(contact_wall);
    if (contact_wall.type == Ball::CollisionType::Left)
    {
      ++iPlayerTwoScore;

      player_two_score->SetScore(iPlayerTwoScore);
    }
    else if (contact_wall.type == Ball::CollisionType::Right)
    {
      ++iPlayerOneScore;

      player_one_score->SetScore(iPlayerOneScore);
    }    
  }

}

Ball::Contact Game::CheckPaddleCollision(Ball const& ball, Paddle const& paddle)
{
  // Check ball's projection on 2D coordinate
	int ball_left   = ball._position.x;
	int ball_right  = ball._position.x + ball._render_info.w;
	int ball_top    = ball._position.y;
	int ball_bottom = ball._position.y + ball._render_info.h;

  // Check paddle's projection on 2D coordinate
	int paddle_left   = paddle._position.x;
	int paddle_right  = paddle._position.x + paddle._render_info.w;
	int paddle_top    = paddle._position.y;
	int paddle_bottom = paddle._position.y + paddle._render_info.h;

	Ball::Contact contact{};

  // Check gaps possible between projection of paddle and ball
  // if any of them exist, there is no collision
	if (ball_left >= paddle_right)
	{
		return contact;
	}

	if (ball_right <= paddle_left)
	{
		return contact;
	}

	if (ball_top >= paddle_bottom)
	{
		return contact;
	}

	if (ball_bottom <= paddle_top)
	{
		return contact;
	}

	float paddle_upper_range = paddle_bottom - (2.0 * paddle._render_info.h / 3.0);
	float paddle_mid_range   = paddle_bottom - (paddle._render_info.h / 3.0);

	if (ball._velocity.x < 0)
	{
		// Left paddle
		contact.penetration = paddle_right - ball_left;
	}
	else if (ball._velocity.x > 0)
	{
		// Right paddle
		contact.penetration = paddle_left - ball_right;
	}

	if ((ball_bottom > paddle_top)
	    && (ball_bottom < paddle_upper_range))
	{
		contact.type = Ball::CollisionType::Top;
	}
	else if ((ball_bottom > paddle_upper_range)
	     && (ball_bottom < paddle_mid_range))
	{
		contact.type = Ball::CollisionType::Middle;
	}
	else
	{
		contact.type = Ball::CollisionType::Bottom;
	}

	return contact;
}

Ball::Contact Game::CheckWallCollision(Ball const& ball)
{
	int ball_left   = ball._position.x;
	int ball_right  = ball._position.x + ball._render_info.w;
	int ball_top    = ball._position.y;
	int ball_bottom = ball._position.y + ball._render_info.h;

	Ball::Contact contact{};

	if (ball_left < 0)
	{
		contact.type = Ball::CollisionType::Left;
	}
	else if (ball_right > _screen_width)
	{
		contact.type = Ball::CollisionType::Right;
	}
	else if (ball_top < 0)
	{
		contact.type = Ball::CollisionType::Top;
		contact.penetration = -ball_top;
	}
	else if (ball_bottom > _screen_height)
	{
		contact.type = Ball::CollisionType::Bottom;
		contact.penetration = _screen_height - ball_bottom;
	}

	return contact;
}