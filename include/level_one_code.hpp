#ifndef LEVEL_ONE_CODE
#define LEVEL_ONE_CODE

#include "code_component.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class LevelOneCode : public engine::CodeComponent {
		private:
			Player *mPlayer;
			std::list<Obstacle *> m_obstacle_list;
			engine::AudioController *mAudioController;
			engine::GameObject *m_losing_parts;
			engine::GameObject *m_losing_death;
			engine::GameObject *mWinningScreen;
			engine::GameObject *mArrow;

			double m_waiting_time = 0.0f;
			int m_current_option = 1;
		public:
			LevelOneCode(engine::GameObject &gameObject);
			void Shutdown();
		private:
			void FindAudioController();
			void UpdateCode();
			void ChangeOption();
			void ChooseOption();
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
