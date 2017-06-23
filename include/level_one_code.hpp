#ifndef LEVEL_ONE_CODE
#define LEVEL_ONE_CODE

#include "code_component.hpp"
#include "player.hpp"
#include "obstacle.hpp"

namespace Azo {
	class LevelOneCode : public engine::CodeComponent {
		private:
			Player *m_player;
			Obstacle *m_obstacle;
		public:
			LevelOneCode(engine::GameObject &game_object);
		private:
			void UpdateCode();
			void UpdateObstaclePosition();
			void GetParents();
	};
}

#endif