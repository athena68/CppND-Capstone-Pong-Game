#ifndef PLAYER_SCORE_H
#define PLAYER_SCORE_H

#include "vector2d.h"
#include "SDL.h"
#include "SDL_ttf.h"

class PlayerScore
{
public:
	PlayerScore(Vector2D position, SDL_Renderer* renderer);
	~PlayerScore();

  	void SetScore(int score);	

	SDL_Renderer* _renderer;
	SDL_Surface* _surface{};
	SDL_Texture* _texture{};
	SDL_Rect _render_info{};
	TTF_Font* font;
};
#endif //PLAYER_SCORE_H