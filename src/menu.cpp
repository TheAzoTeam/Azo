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
	m_menu->addComponent(*mAudioController);

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

	m_animation_controller->addAnimation("start_button", *m_start_button);

	m_arrow_start = new engine::Animation(*m_menu,
					      "general_images/textos.png",
					      1.0f,
					      m_arrow_sprites,
					      0,
					      0,
					      false,
					      1,
					      std::make_pair(168, 162));

	m_animation_controller->addAnimation("arrow_start", *m_arrow_start);

	m_exit_button = new engine::Animation(*m_menu,
					      "general_images/textos.png",
					      1.0f,
					      m_exit_button_sprites,
					      0,
					      0,
					      false,
					      1,
					      std::make_pair(551, 162));

	m_animation_controller->addAnimation("exit_button", *m_exit_button);

	m_arrow_exit = new engine::Animation(*m_menu,
					     "general_images/textos.png",
					     1.0f,
					     m_arrow_sprites,
					     0,
					     0,
					     false,
					     1,
					     std::make_pair(514, 162));

	m_arrow_exit->disableComponent();
	m_animation_controller->addAnimation("arrow_exit", *m_arrow_exit);

	m_sound_enable_button = new engine::Animation(*m_menu,
						      "general_images/textos.png",
						      1.0f,
						      m_sound_enabled_button_sprites,
						      0,
						      0,
						      false,
						      1,
						      std::make_pair(708, 40));

	m_animation_controller->addAnimation("sound_enabled_button", *m_sound_enable_button);

	m_sound_disabled_button = new engine::Animation(*m_menu,
							"general_images/textos.png",
							1.0f,
							m_sound_disabled_button_sprites,
							0,
							0,
							false,
							1,
							std::make_pair(708, 40));

	m_sound_disabled_button->disableComponent();

	m_animation_controller->addAnimation("sound_disabled_button", *m_sound_disabled_button);

	m_arrow_sound = new engine::Animation(*m_menu,
					      "general_images/textos.png",
					      1.0f,
					      m_arrow_sprites,
					      0,
					      0,
					      false,
					      1,
					      std::make_pair(676, 40));

	m_arrow_sound->disableComponent();

	m_animation_controller->addAnimation("arrow_sound", *m_arrow_sound);

	m_menu->addComponent(*m_animation_controller);

	m_background = new engine::BackgroundComponent(*m_menu, "backgrounds/menu.png");
	m_menu->addComponent(*m_background);

	m_code = new MenuCode(m_menu);
	m_menu->addComponent(*m_code);
}

void Menu::GenButtonsAnimation(){
	m_start_button_sprites.push_back(new engine::Sprite());

	m_start_button_sprites[0]->spriteX = 43;
	m_start_button_sprites[0]->spriteY = 452;
	m_start_button_sprites[0]->spriteWidth = 161 - 43;
	m_start_button_sprites[0]->spriteHeight = 478 - 452;

	m_exit_button_sprites.push_back(new engine::Sprite());

	m_exit_button_sprites[0]->spriteX = 207;
	m_exit_button_sprites[0]->spriteY = 413;
	m_exit_button_sprites[0]->spriteWidth = 280 - 207;
	m_exit_button_sprites[0]->spriteHeight = 441 - 413;

	m_sound_enabled_button_sprites.push_back(new engine::Sprite());

	m_sound_enabled_button_sprites[0]->spriteX = 660;
	m_sound_enabled_button_sprites[0]->spriteY = 46;
	m_sound_enabled_button_sprites[0]->spriteWidth = 702 - 660;
	m_sound_enabled_button_sprites[0]->spriteHeight = 77 - 46;

	m_sound_disabled_button_sprites.push_back(new engine::Sprite());

	m_sound_disabled_button_sprites[0]->spriteX = 608;
	m_sound_disabled_button_sprites[0]->spriteY = 46;
	m_sound_disabled_button_sprites[0]->spriteWidth = 646 - 608;
	m_sound_disabled_button_sprites[0]->spriteHeight = 77 - 46;

	m_arrow_sprites.push_back(new engine::Sprite());

	m_arrow_sprites[0]->spriteX = 582;
	m_arrow_sprites[0]->spriteY = 433;
	m_arrow_sprites[0]->spriteWidth = 598 - 582;
	m_arrow_sprites[0]->spriteHeight = 459 - 433;
}


void Menu::shutdown(){
	DEBUG("Calling Menu::shutdown.");
}
