#ifndef GAME_H
#define GAME_H

#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "paddles.h"
#include "ball.h"
#include "player_score.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height, 
       std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

 private:
  std::unique_ptr<Paddle> paddle_one;
  std::unique_ptr<Paddle> paddle_two;
  std::unique_ptr<Ball> ball;
  std::unique_ptr<PlayerScore> player_one_score;
  std::unique_ptr<PlayerScore> player_two_score;  

  std::size_t _screen_width;
  std::size_t _screen_height;

  void Update(Uint32 dTime, int &iPlayerOneScore, int &iPlayerTwoScore);
  Ball::Contact CheckPaddleCollision(Ball const& ball, Paddle const& paddle);
  Ball::Contact CheckWallCollision(Ball const& ball);
};

#endif