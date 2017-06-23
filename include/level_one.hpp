#ifndef LEVEL_ONE
#define LEVEL_ONE

#include "scene.hpp"
#include "player.hpp"

namespace Azo {
	class LevelOne : public engine::Scene {
		public:
			LevelOne();
			LevelOne(std::string name);
		private:
			Player *m_player;
			engine::GameObject *m_level_one;
			engine::ImageComponent *m_level_background;
		private:
			void CreateGameObjects();
			void CreateLevelComponents();
	};
}

#endif