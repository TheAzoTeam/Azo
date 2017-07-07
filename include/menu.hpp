#ifndef MENU
#define MENU

#include "scene.hpp"
#include "menu_code.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class Menu : public engine::Scene {
		private:
			engine::GameObject *m_menu;

			engine::AnimationController *m_animation_controller;

			engine::Animation *m_start_button;
			engine::Animation *m_exit_button;
			engine::Animation *m_sound_enable_button;
			engine::Animation *m_sound_disabled_button;

			engine::Animation *m_arrow_start;
			engine::Animation *m_arrow_exit;
			engine::Animation *m_arrow_sound;

			std::vector<engine::Sprite *> m_start_button_sprites;
			std::vector<engine::Sprite *> m_exit_button_sprites;
			std::vector<engine::Sprite *> m_sound_enabled_button_sprites;
			std::vector<engine::Sprite *> m_sound_disabled_button_sprites;

			std::vector<engine::Sprite *> m_arrow_sprites;

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
			void GenButtonsAnimation();

	};
}

#endif