#ifndef LEVEL_ONE_CODE
#define LEVEL_ONE_CODE

#include "code_component.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class LevelOneCode : public engine::CodeComponent {
		private:
			Player *m_player;
			std::list<Obstacle *> m_obstacle_list;
			Obstacle *m_ground;
			engine::AudioController *m_audio_controller;
		public:
			LevelOneCode(engine::GameObject &game_object);
		private:
			void FindAudioController();
			void UpdateCode();
			void UpdateObstaclePosition();
			void GetParents();
			bool HasGround(double *ground_y);
			bool CheckCollisionWithLevelGround(
				double player_top,
				double player_bottom,
				double player_left,
				double player_right,
				double *ground_y);

			bool HasCeiling(double *ground_y);
			bool HasWallOnRight(double *wall_x);
			bool HasWallOnLeft(double *wall_x);
			void UpdatePhysics();

	};
}

#endif
