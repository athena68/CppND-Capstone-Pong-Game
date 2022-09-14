#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, Paddle &paddle_one, Paddle &paddle_two) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          paddle_one.ChangeDirection(Paddle::Direction::kUp);
          break;

        case SDLK_DOWN:
          paddle_one.ChangeDirection(Paddle::Direction::kDown);
          break;

        case SDLK_w:
          paddle_two.ChangeDirection(Paddle::Direction::kUp);
          break;

        case SDLK_s:
          paddle_two.ChangeDirection(Paddle::Direction::kDown);
          break;
      }
    } else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {      
        case SDLK_UP:
          paddle_one.ChangeDirection(Paddle::Direction::kOnHold);
          break;

        case SDLK_DOWN:
          paddle_one.ChangeDirection(Paddle::Direction::kOnHold);
          break;

        case SDLK_w:
          paddle_two.ChangeDirection(Paddle::Direction::kOnHold);
          break;

        case SDLK_s:
          paddle_two.ChangeDirection(Paddle::Direction::kOnHold);
          break;
      }
    }
  }
}