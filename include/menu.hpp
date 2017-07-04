#ifndef MENU
#define MENU

#include "scene.hpp"
#include "menu_code.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class Menu : public engine::Scene {
		private:
			engine::GameObject *m_menu;
			engine::BackgroundComponent *m_background;
			MenuCode *m_code;
			engine::AudioController *m_audio_controller;
			engine::AudioComponent *m_menu_theme;
		public:
			Menu();
			Menu(std::string name);
			void Restart();
			void Shutdown();
		private:
			void CreateGameObjects();
			void CreateMenuComponents();
	};
}

#endif