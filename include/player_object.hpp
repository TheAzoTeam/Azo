#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include "game_object.hpp"
#include "sdl2include.h"
class PlayerObject : public engine::GameObject {
	public:
		PlayerObject() : engine::GameObject("player_object") {
		};
		virtual bool Init(SDL_Renderer *);
		virtual bool Draw(SDL_Renderer *);
		virtual bool Shutdown();
	private:
		SDL_Texture *player_object_texture;
};

#endif