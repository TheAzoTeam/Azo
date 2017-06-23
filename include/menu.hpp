#ifndef MENU
#define MENU

#include "scene.hpp"
#include "menu_code.hpp"

namespace Azo {
	class Menu : public engine::Scene {
		private:
			engine::GameObject *m_menu;
			engine::BackgroundComponent *m_background;
			MenuCode *m_code;
		public:
			Menu();
			Menu(std::string name);
		private:
			void CreateGameObjects();
			void CreateMenuComponents();
	};
}

#endif