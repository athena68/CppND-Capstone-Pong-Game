#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "ball.h"
#include "paddles.h"
#include "player_score.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Ball const &ball, Paddle const &paddle_one, Paddle const &paddle_two,
              PlayerScore const &player_one_score, PlayerScore const &player_two_score);

  SDL_Renderer* GetRenderer() const;

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height; 
};

#endif