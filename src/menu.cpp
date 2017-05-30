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
	menu_image = new engine::ImageComponent(*menu_game_object, "backgrounds/menu.png");
	menu_code = new MenuCode(*menu_game_object);
}

void Menu::SetGameObjects(){
	ASSERT(play_button_menu != NULL, "Play button menu can't be NULL.");
	ASSERT(menu_game_object != NULL, "Menu game object can't be NULL.");

	this->AddGameObject(*play_button_menu);
	this->AddGameObject(*menu_game_object);
}
void Menu::SetComponents(){
	ASSERT(play_button_menu != NULL, "Play button menu can't be NULL.");
	ASSERT(menu_game_object != NULL, "Menu game object can't be NULL.");
	ASSERT(menu_image != NULL, "Menu image can't be NULL.");
	ASSERT(play_button_image != NULL, "Play button image object can't be NULL.");
	ASSERT(menu_code != NULL, "Menu Code can't be NULL.");

	menu_game_object->AddComponent(*menu_image);
	play_button_menu->AddComponent(*play_button_image);
	menu_game_object->AddComponent(*menu_code);
}

bool Menu::Shutdown(){
	INFO("Destroying Menu.");
	DestroyComponents();
	DestroyGameObjects();
	return true;
}

void Menu::DestroyComponents(){
	INFO("Destroying Menu Components.");
	play_button_image->Shutdown();
	free(play_button_image);
	play_button_image = NULL;

	menu_image->Shutdown();
	free(menu_image);
	menu_image = NULL;

	menu_code->Shutdown();
	free(menu_code);
	menu_image = NULL;
}
void Menu::DestroyGameObjects(){
	INFO("Destroying GameObjects.");
	free(menu_game_object);
	DEBUG("Freeing Menu pointer.");
	menu_game_object = NULL;
	DEBUG("Cleaning menu reference.");

	free(play_button_menu);
	DEBUG("Freeing play button menu.");
	play_button_menu = NULL;
	DEBUG("Cleaning play button reference.");
}