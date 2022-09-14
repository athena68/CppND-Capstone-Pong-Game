#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize TTF
	if (TTF_Init() < 0) {
		std::cerr << "Failed to initialise SDL_ttf.\n";
    std::cerr << "SDL_ttf error: " << TTF_GetError() << "\n";
	}  

  // Create Window
  sdl_window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  TTF_Quit();  
  SDL_Quit();
}

void Renderer::Render(Ball const &ball, 
                      Paddle const &paddle_one, Paddle const &paddle_two, 
                      PlayerScore const &player_one_score, PlayerScore const &player_two_score) {

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Set the draw color to be white
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  // Draw the center net
  for (int i = 0; i < screen_width; ++i) {
    if (i % 5) {
      SDL_RenderDrawPoint(sdl_renderer, screen_width / 2, i);
    }
  }  

  // Render Ball
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &(ball._render_info));

  // Render Paddles
  SDL_RenderFillRect(sdl_renderer, &(paddle_one._render_info));
  SDL_RenderFillRect(sdl_renderer, &(paddle_two._render_info));  

  // Render the scores
  SDL_RenderCopy(sdl_renderer, player_one_score._texture, nullptr, &(player_one_score._render_info));
  SDL_RenderCopy(sdl_renderer, player_two_score._texture, nullptr, &(player_two_score._render_info));

  SDL_RenderPresent(sdl_renderer);
}

  SDL_Renderer* Renderer::GetRenderer() const 
  {
    return sdl_renderer;
  }
