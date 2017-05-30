#include "menu.hpp"

using namespace Azo;

Menu::Menu(){}

Menu::~Menu(){}

Menu::Menu(std::string scene_name){
	this->scene_name = scene_name;
	SetMenuDependencies();
}

void Menu::SetMenuDependencies(){
	engine::GameObject *menu_game_object = new engine::GameObject("menu_game_object", 0, 0);
	engine::GameObject *play_button_menu = new engine::GameObject("play_button_menu", 300, 300);

	engine::ImageComponent *play_button_image = new engine::ImageComponent(*play_button_menu, "backgrounds/play_button.png");
	engine::BackgroundComponent *menu_image = new engine::BackgroundComponent(*menu_game_object, "backgrounds/menu.png");

	menu_game_object->AddComponent(*menu_image);
	play_button_menu->AddComponent(*play_button_image);

	menu_code.SetGameObject(*menu_game_object);

	menu_game_object->AddComponent(menu_code);

	this->AddGameObject(*play_button_menu);
	this->AddGameObject(*menu_game_object);
}

