#ifndef LEVEL_ONE_CODE
#define LEVEL_ONE_CODE

#include "code_component.hpp"
#include "player.hpp"
#include "obstacle.hpp"

namespace Azo {
	class LevelOneCode : public engine::CodeComponent {
		private:
			Player *m_player;
			std::list<Obstacle *> m_obstacle_list;
		public:
			LevelOneCode(engine::GameObject &game_object);
		private:
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