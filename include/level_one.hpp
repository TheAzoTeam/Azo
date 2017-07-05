#ifndef LEVEL_ONE
#define LEVEL_ONE

#include "scene.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "level_one_code.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class LevelOne : public engine::Scene {
		private:
			// This is the level game object. It contains things such as background, theme, etc.
			engine::GameObject *m_level_one;

			// Add new components to level one here.
			engine::ImageComponent *m_level_background_1;
			engine::ImageComponent *m_level_background_2;
			engine::ImageComponent *m_level_background_3;
			engine::AudioController *m_audio_controller;
			engine::AudioComponent *m_level_theme;
			LevelOneCode *m_level_code;

			Player *m_player;

			// Add obstacles here
			Obstacle *m_obstacle_car_1;
			Obstacle *m_obstacle_aerial_1;
			Obstacle *m_part_1;
			Obstacle *m_obstacle_aerial_2;
			Obstacle *m_obstacle_aerial_3;
			Obstacle *m_part_2;
			Obstacle *m_obstacle_box_1;
			Obstacle *m_obstacle_box_2;
			Obstacle *m_obstacle_aerial_4;
			Obstacle *m_part_3;
			Obstacle *m_obstacle_car_2;
			Obstacle *m_part_4;
			Obstacle *m_obstacle_aerial_5;
			Obstacle *m_obstacle_aerial_6;
			Obstacle *m_part_5;
			Obstacle *m_obstacle_box_3;
			Obstacle *m_obstacle_rock_1;
			Obstacle *m_part_6;
			Obstacle *m_obstacle_aerial_7;
			Obstacle *m_obstacle_rock_2;
			Obstacle *m_part_7;
			Obstacle *m_obstacle_aerial_8;
			Obstacle *m_obstacle_aerial_9;
			Obstacle *m_part_8;
			Obstacle *m_part_1_1;
			Obstacle *m_part_4_1;
			Obstacle *m_part_7_1;
			Obstacle *m_part_9;
			Obstacle *m_obstacle_aerial_10;
			Obstacle *m_part_10;
			Obstacle *m_obstacle_box_0_1;
			Obstacle *m_obstacle_box_2_1;
			Obstacle *m_ground;

		private:
			//Don't forget to add the new objects using this function.
			void CreateGameObjects();

			// After adding things that collide (obstacles, for exemple), add they as paren'ts here.
			void AddLevelParents();
		public:
			LevelOne();
			LevelOne(std::string name);
			void Restart();
	};
}

#endif
