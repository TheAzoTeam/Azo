#ifndef LEVEL_ONE_HPP
#define LEVEL_ONE_HPP

#include "scene.hpp"
#include "floor.hpp"
#include "wall.hpp"
#include "player.hpp"

#include <string>

namespace Azo {
	class LevelOne : public engine::Scene {
		private:
			Player *player;
			Floor *floor_platform;
			Floor *floor_plataform_two;
			Wall *wall;
		public:
			LevelOne();
			LevelOne(std::string name);
			void UpdateCode();
			bool apply_update = false;
		private:
			void SetDependencies();
			void CreateGameObjects();
			void SetGameObjects();
			void Shutdown();
			void DestroyGameObjects();
	};
}

#endif
