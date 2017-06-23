#ifndef MENU
#define MENU

#include "scene.hpp"

namespace Azo {
	class Menu : public engine::Scene {
		private:
			engine::GameObject *m_menu;
			engine::BackgroundComponent *m_background;
		public:
			Menu();
			Menu(std::string name);
		private:
			void CreateGameObjects();
			void CreateMenuComponents();
	};
}

#endif