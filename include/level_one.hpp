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

			engine::BackgroundComponent *m_winning_screen;
			engine::BackgroundComponent *m_losing_parts_screen;
			engine::BackgroundComponent *m_losing_death_screen;

			engine::GameObject *m_winning_screen_object;
			engine::GameObject *m_losing_parts_screen_object;
			engine::GameObject *m_losing_death_screen_object;
			engine::GameObject *m_arrow;
			engine::ImageComponent *m_arrow_image;

			engine::ImageComponent *m_level_background_1;
			engine::ImageComponent *m_level_background_2;
			engine::ImageComponent *m_level_background_3;

			// This is the level game object. It contains things such as background, theme, etc.
			engine::GameObject *m_level_one;

			// Add new components to level one here.

			engine::AudioController *mAudioController;
			engine::AudioComponent *m_level_theme;
			LevelOneCode *m_level_code;

			Player *m_player;

			// Add obstacles here
			obstacle *m_obstacle_car_1;
			obstacle *m_spike_1;
			obstacle *m_obstacle_aerial_1;
			obstacle *m_part_1;
			obstacle *m_obstacle_aerial_2;
			obstacle *m_obstacle_aerial_3;
			obstacle *m_part_2;
			obstacle *m_obstacle_box_1;
			obstacle *m_obstacle_box_2;
			obstacle *m_obstacle_aerial_4;
			obstacle *m_part_3;
			obstacle *m_obstacle_car_2;
			obstacle *m_part_4;
			obstacle *m_obstacle_aerial_5;
			obstacle *m_obstacle_aerial_6;
			obstacle *m_part_5;
			obstacle *m_obstacle_box_3;
			obstacle *m_obstacle_rock_1;
			obstacle *m_part_6;
			obstacle *m_obstacle_aerial_7;
			obstacle *m_obstacle_rock_2;
			obstacle *m_part_7;
			obstacle *m_obstacle_aerial_8;
			obstacle *m_obstacle_aerial_9;
			obstacle *m_part_8;
			obstacle *m_part_1_1;
			obstacle *m_part_4_1;
			obstacle *m_part_7_1;
			obstacle *m_part_9;
			obstacle *m_obstacle_aerial_10;
			obstacle *m_part_10;
			obstacle *m_obstacle_box_0_1;
			obstacle *m_obstacle_box_2_1;
			obstacle *m_obstacle_car_3;
			obstacle *m_part_11;
			obstacle *m_obstacle_aerial_11;
			obstacle *m_part_12;
			obstacle *m_obstacle_aerial_12;
			obstacle *m_part_13;
			obstacle *m_part_14;
			obstacle *m_part_15;
			obstacle *m_part_16;
			obstacle *m_obstacle_aerial_13;
			obstacle *m_spike_2;
			obstacle *m_obstacle_box_4;
			obstacle *m_spike_3;
			obstacle *m_obstacle_box_5;
			obstacle *m_spike_4;
			obstacle *m_obstacle_box_6;
			obstacle *m_obstacle_aerial_14;
			obstacle *m_obstacle_box_7;
			obstacle *m_obstacle_aerial_15;
			obstacle *m_part_17;
			obstacle *m_obstacle_rock_3;
			obstacle *m_obstacle_box_8;
			obstacle *m_part_18;
			obstacle *m_obstacle_aerial_16;
			obstacle *m_obstacle_rock_4;
			obstacle *m_obstacle_rock_5;
			obstacle *m_obstacle_aerial_17;
			obstacle *m_obstacle_box_9;
			obstacle *m_obstacle_box_10;
			obstacle *m_obstacle_aerial_18;
			obstacle *m_obstacle_aerial_19;
			obstacle *m_part_19;
			obstacle *m_obstacle_rock_6;
			obstacle *m_obstacle_rock_7;
			obstacle *m_obstacle_rock_8;
			obstacle *m_obstacle_car_4;
			obstacle *m_part_20;
			obstacle *m_obstacle_car_5;
			obstacle *m_spike_5;
			obstacle *m_obstacle_box_11;
			obstacle *m_obstacle_aerial_20;
			obstacle *m_part_21;
			obstacle *m_obstacle_aerial_21;
			obstacle *m_obstacle_rock_9;
			obstacle *m_obstacle_aerial_22;
			obstacle *m_part_22;
			obstacle *m_ground;

		private:
			//Don't forget to add the new objects using this function.
			void CreateGameObjects();
			void CreateEndingScreen();

			// After adding things that collide (obstacles, for exemple), add they as paren'ts here.
			void AddLevelParents();
		public:
			LevelOne();
			LevelOne(std::string name);
			void Restart();
	};
}

#endif
