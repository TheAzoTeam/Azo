#include "menu.hpp"

using namespace Azo;

Menu::Menu(std::string name){
	this->scene_name = name;
	CreateGameObjects();
}

void Menu::Restart(){
	gameObject_map.clear();
	CreateGameObjects();
}

void Menu::CreateGameObjects(){
	DEBUG("Creating Menu GameObjects.");

	m_menu = new engine::GameObject("menu", std::make_pair(0, 0));
	CreateMenuComponents();

	this->AddGameObject(*m_menu);
}

void Menu::CreateMenuComponents(){
	m_menu_theme = new engine::AudioComponent(*m_menu, "audios/TemaGame.ogg", true, true);
	mAudioController = new engine::AudioController();
	mAudioController->AddAudio("menu_theme", *m_menu_theme);
	m_menu->AddComponent(*mAudioController);

	m_animation_controller = new engine::AnimationController(*m_menu);

	GenButtonsAnimation();
	m_start_button = new engine::Animation(*m_menu,
					       "general_images/textos.png",
					       1.0f,
					       m_start_button_sprites,
					       0,
					       0,
					       false,
					       1,
					       std::make_pair(205, 162));

	m_animation_controller->AddAnimation("start_button", *m_start_button);

	m_arrow_start = new engine::Animation(*m_menu,
					      "general_images/textos.png",
					      1.0f,
					      m_arrow_sprites,
					      0,
					      0,
					      false,
					      1,
					      std::make_pair(168, 162));

	m_animation_controller->AddAnimation("arrow_start", *m_arrow_start);

	m_exit_button = new engine::Animation(*m_menu,
					      "general_images/textos.png",
					      1.0f,
					      m_exit_button_sprites,
					      0,
					      0,
					      false,
					      1,
					      std::make_pair(551, 162));

	m_animation_controller->AddAnimation("exit_button", *m_exit_button);

	m_arrow_exit = new engine::Animation(*m_menu,
					     "general_images/textos.png",
					     1.0f,
					     m_arrow_sprites,
					     0,
					     0,
					     false,
					     1,
					     std::make_pair(514, 162));

	m_arrow_exit->DisableComponent();
	m_animation_controller->AddAnimation("arrow_exit", *m_arrow_exit);

	m_sound_enable_button = new engine::Animation(*m_menu,
						      "general_images/textos.png",
						      1.0f,
						      m_sound_enabled_button_sprites,
						      0,
						      0,
						      false,
						      1,
						      std::make_pair(708, 40));

	m_animation_controller->AddAnimation("sound_enabled_button", *m_sound_enable_button);

	m_sound_disabled_button = new engine::Animation(*m_menu,
							"general_images/textos.png",
							1.0f,
							m_sound_disabled_button_sprites,
							0,
							0,
							false,
							1,
							std::make_pair(708, 40));

	m_sound_disabled_button->DisableComponent();

	m_animation_controller->AddAnimation("sound_disabled_button", *m_sound_disabled_button);

	m_arrow_sound = new engine::Animation(*m_menu,
					      "general_images/textos.png",
					      1.0f,
					      m_arrow_sprites,
					      0,
					      0,
					      false,
					      1,
					      std::make_pair(676, 40));

	m_arrow_sound->DisableComponent();

	m_animation_controller->AddAnimation("arrow_sound", *m_arrow_sound);

	m_menu->AddComponent(*m_animation_controller);

	m_background = new engine::BackgroundComponent(*m_menu, "backgrounds/menu.png");
	m_menu->AddComponent(*m_background);

	m_code = new MenuCode(m_menu);
	m_menu->AddComponent(*m_code);
}

void Menu::GenButtonsAnimation(){
	m_start_button_sprites.push_back(new engine::Sprite());

	m_start_button_sprites[0]->sprite_x = 43;
	m_start_button_sprites[0]->sprite_y = 452;
	m_start_button_sprites[0]->sprite_width = 161 - 43;
	m_start_button_sprites[0]->sprite_height = 478 - 452;

	m_exit_button_sprites.push_back(new engine::Sprite());

	m_exit_button_sprites[0]->sprite_x = 207;
	m_exit_button_sprites[0]->sprite_y = 413;
	m_exit_button_sprites[0]->sprite_width = 280 - 207;
	m_exit_button_sprites[0]->sprite_height = 441 - 413;

	m_sound_enabled_button_sprites.push_back(new engine::Sprite());

	m_sound_enabled_button_sprites[0]->sprite_x = 660;
	m_sound_enabled_button_sprites[0]->sprite_y = 46;
	m_sound_enabled_button_sprites[0]->sprite_width = 702 - 660;
	m_sound_enabled_button_sprites[0]->sprite_height = 77 - 46;

	m_sound_disabled_button_sprites.push_back(new engine::Sprite());

	m_sound_disabled_button_sprites[0]->sprite_x = 608;
	m_sound_disabled_button_sprites[0]->sprite_y = 46;
	m_sound_disabled_button_sprites[0]->sprite_width = 646 - 608;
	m_sound_disabled_button_sprites[0]->sprite_height = 77 - 46;

	m_arrow_sprites.push_back(new engine::Sprite());

	m_arrow_sprites[0]->sprite_x = 582;
	m_arrow_sprites[0]->sprite_y = 433;
	m_arrow_sprites[0]->sprite_width = 598 - 582;
	m_arrow_sprites[0]->sprite_height = 459 - 433;
}


void Menu::shutDown(){
	DEBUG("Calling Menu::shutDown.");
}