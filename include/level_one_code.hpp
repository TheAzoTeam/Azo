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
			engine::AudioController *m_audio_controller;
			engine::GameObject *m_losing_parts;
			engine::GameObject *m_losing_death;
			engine::GameObject *m_winning_screen;
			engine::GameObject *m_arrow;

			double m_waiting_time = 0.0f;
		public:
			LevelOneCode(engine::GameObject &game_object);
			void Shutdown();
		private:
			void FindAudioController();
			void UpdateCode();
			void UpdateObstaclePosition();
			void GetParents();
			bool HasGround(double *ground_y);
			bool HasCeiling(double *ground_y);
			bool HasWallOnRight(double *wall_x);
			bool HasWallOnLeft(double *wall_x);
			void UpdatePhysics();

	};
}

#endif
