#ifndef LEVEL_ONE
#define LEVEL_ONE

#include "scene.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "level_one_code.hpp"
#include "audio_controller.hpp"
#include "machine_part.hpp"

namespace Azo {
	class LevelOne : public engine::Scene {
		public:
			LevelOne();
			LevelOne(std::string name);
		private:
			engine::GameObject *m_level_one;

			engine::ImageComponent *m_level_background;
			LevelOneCode *m_level_code;
			engine::AudioController *m_audio_controller;
			engine::AudioComponent *m_level_theme;

			Player *m_player;

			Obstacle *m_obstacle;
			Obstacle *m_ground;

			MachinePart *m_part;

		private:
			void CreateGameObjects();
			void CreateLevelComponents();
			void AddLevelParents();
	};
}

#endif