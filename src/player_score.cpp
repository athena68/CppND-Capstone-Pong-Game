#include "player_score.h"
#include <iostream>
#include <string>

PlayerScore::PlayerScore(Vector2D position, SDL_Renderer* renderer)
    : _renderer(renderer)
{
    // Initialize the font
    font = TTF_OpenFont("OpenSans-Regular.ttf", 40);

    if (font == NULL) {
        std::cerr << "Failed to load font\n";
        std::cerr << "SDL_ttf error: " << TTF_GetError() << "\n";
    }

    _surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
    _texture = SDL_CreateTextureFromSurface(renderer, _surface);

    int width, height;
    SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);

    _render_info.x = position.x;
    _render_info.y = position.y;
    _render_info.w = width;
    _render_info.h = height;
}

PlayerScore::~PlayerScore()
{
    TTF_CloseFont(font);    
    SDL_FreeSurface(_surface);
    SDL_DestroyTexture(_texture);
}

void PlayerScore::SetScore(int score)
{
  SDL_FreeSurface(_surface);
  SDL_DestroyTexture(_texture);

  _surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
  _texture = SDL_CreateTextureFromSurface(_renderer, _surface);

  int width, height;
  SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);
  _render_info.w = width;
  _render_info.h = height;
}