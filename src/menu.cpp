#include "menu.hpp"

using namespace Azo;

Menu::Menu(){}

Menu::~Menu(){}

Menu::Menu(std::string scene_name){
	this->scene_name = scene_name;
	SetMenuDependencies();
}

void Menu::SetMenuDependencies(){
	CreateGameObjects();
	CreateComponents();
	SetComponents();
	SetGameObjects();
}

void Menu::CreateGameObjects(){
	menu_game_object = new engine::GameObject("menu_game_object", 0, 0);
	play_button_menu = new engine::GameObject("play_button_menu", 300, 300);
}
void Menu::CreateComponents(){
	play_button_image = new engine::ImageComponent(*play_button_menu, "backgrounds/play_button.png");
	menu_image = new engine::BackgroundComponent(*menu_game_object, "backgrounds/menu.png");
	menu_code = new MenuCode(*menu_game_object);
}

void Menu::SetGameObjects(){
	this->AddGameObject(*play_button_menu);
	this->AddGameObject(*menu_game_object);
}
void Menu::SetComponents(){
	menu_game_object->AddComponent(*menu_image);
	play_button_menu->AddComponent(*play_button_image);

	menu_game_object->AddComponent(*menu_code);
}