#ifndef LEVEL_ONE_CODE
#define LEVEL_ONE_CODE

#include "code_component.hpp"
#include "player.hpp"

namespace Azo {
	class LevelOneCode : public engine::CodeComponent {
		private:
			Player *m_player;
		public:
			LevelOneCode(engine::GameObject &game_object);
		private:
			void UpdateCode();
			void GetParents();
	};
}

#endif