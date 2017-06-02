#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include "menu.hpp"
#include "level_one.hpp"

namespace Azo {
	class LevelManager {
		private:
			Menu *menu;
			LevelOne *level_one;
		public:
			static LevelManager level_manager;
			LevelManager();
			void GoToMenu();
			void GoToLevelOne();
		private:
			void CreateMenu();
			void CreateLevelOne();

	};
}

#endif