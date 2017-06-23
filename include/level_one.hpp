#ifndef LEVEL_ONE
#define LEVEL_ONE

#include "scene.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "level_one_code.hpp"

namespace Azo {
	class LevelOne : public engine::Scene {
		public:
			LevelOne();
			LevelOne(std::string name);
		private:
			Player *m_player;
			engine::GameObject *m_level_one;
			Obstacle *m_obstacle;

			engine::ImageComponent *m_level_background;
			LevelOneCode *m_level_code;
		private:
			void CreateGameObjects();
			void CreateLevelComponents();
			void AddLevelParents();
	};
}

#endif