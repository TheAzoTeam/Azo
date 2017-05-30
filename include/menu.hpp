#ifndef MENU_HPP
#define MENU_HPP

#include <string>

#include "scene.hpp"
#include "menu_code.hpp"
#include "background_component.hpp"

namespace Azo {
	class Menu : public engine::Scene {
		private:
			MenuCode *menu_code;
			engine::GameObject *menu_game_object;
			engine::GameObject *play_button_menu;

			engine::ImageComponent *play_button_image;
			engine::BackgroundComponent *menu_image;
		public:
			Menu();
			~Menu();
			Menu(std::string scene_name);
		private:
			void SetMenuDependencies();
			void CreateGameObjects();
			void CreateComponents();
			void SetGameObjects();
			void SetComponents();
			bool Shutdown();
			void DestroyComponents();
			void DestroyGameObjects();
	};
}

#endif