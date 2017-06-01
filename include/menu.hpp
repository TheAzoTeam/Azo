#ifndef MENU_HPP
#define MENU_HPP

#include <string>

#include "scene.hpp"
#include "menu_code.hpp"
#include "moving_image_component.hpp"
#include "image_component.hpp"
#include "audio_controller.hpp"
#include "disable_sound_code.hpp"

namespace Azo {
	class Menu : public engine::Scene {
		private:
			engine::GameObject *menu_game_object;
			MenuCode *menu_code;
			engine::AudioController *audio_controller;
			engine::AudioComponent *menu_theme;
			engine::BackgroundComponent *menu_image;
			engine::ImageComponent *disable_sound_image;
			engine::ImageComponent *play_button_image;
		public:
			Menu();
			~Menu();
			Menu(std::string scene_name);
		private:
			void CreateGameObjects();
			void CreateImageComponents();
			void CreateBackgroundComponents();
			void CreateCodeComponents();
			void CreateAudioComponents();

			void SetGameObjects();
			void SetImageComponents();
			void SetBackgroundComponents();
			void SetCodeComponents();
			void SetAudioComponents();

			void SetMenuDependencies();
			bool Shutdown();
			void DestroyComponents();
			void DestroyGameObjects();
	};
}

#endif
