#ifndef PLAYER_SCENE_HPP
#define PLAYER_SCENE_HPP

#include "scene.hpp"

class PlayerScene : public engine::Scene {
	public:
		PlayerScene();
		~PlayerScene();

		bool Init(SDL_Renderer *canvas);
		bool Shutdown();

		bool Draw(SDL_Renderer *canvas);
};

#endif