#include "menu.hpp"

using namespace Azo;

Menu::Menu(){}

Menu::Menu(std::string scene_name){
	this->scene_name = scene_name;
	SetMenuDependencies();
}

Menu::~Menu(){}

void Menu::SetMenuDependencies(){
	CreateGameObjects();

	CreateBackgroundComponents();
	SetBackgroundComponents();

	CreateImageComponents();
	SetImageComponents();

	CreateAudioComponents();
	SetAudioComponents();

	CreateCodeComponents();
	SetCodeComponents();

	SetGameObjects();
}

void Menu::CreateGameObjects(){
	menu_game_object = new engine::GameObject("menu_game_object", 0, 0);
}

void Menu::CreateImageComponents(){
	DEBUG("Creating Image Components");
	disable_sound_image = new engine::ImageComponent(
		*menu_game_object,
		"general_images/disable_sound.png",
		0,
		500
		);

	play_button_image = new engine::ImageComponent(
		*menu_game_object,
		"backgrounds/play_button.png",
		300,
		300
		);
}

void Menu::CreateBackgroundComponents(){
	DEBUG("Creating Background Components");

	menu_image = new engine::BackgroundComponent(*menu_game_object, "backgrounds/menu.png");
}

void Menu::CreateCodeComponents(){
	DEBUG("Creating Code Components");

	menu_code = new MenuCode(*menu_game_object);
}

void Menu::SetCodeComponents(){
	DEBUG("Setting Code Components");

	ASSERT(menu_code != NULL, "Menu Code can't be NULL.");

	menu_game_object->AddComponent(*menu_code);
}


void Menu::CreateAudioComponents(){
	DEBUG("Creating Audio Components");

	menu_theme = new engine::AudioComponent(*menu_game_object, "audios/TemaGame.ogg", true, true);
	audio_controller = new engine::AudioController();
}

void Menu::SetAudioComponents(){
	DEBUG("Setting Audio Components");

	ASSERT(menu_theme != NULL, "Menu Theme can't be NULL.");
	ASSERT(audio_controller != NULL, "Audio controller can't be NULL.");
	ASSERT(audio_controller != NULL, "Audio controller can't be null");

	audio_controller->AddAudio("menu_theme", *menu_theme);
	menu_game_object->AddComponent(*audio_controller);
}

void Menu::SetGameObjects(){
	DEBUG("Setting Menu Game Objects");
	ASSERT(menu_game_object != NULL, "Menu game object can't be NULL.");

	this->AddGameObject(*menu_game_object);
}

void Menu::SetImageComponents(){
	DEBUG("Setting Image Components");

	ASSERT(play_button_image != NULL, "Play button image object can't be NULL.");
	ASSERT(disable_sound_image != NULL, "Disable Sound Image can't be NULL.");

	menu_game_object->AddComponent(*play_button_image);
	menu_game_object->AddComponent(*disable_sound_image);
}

void Menu::SetBackgroundComponents(){
	DEBUG("Setting Background Components");

	ASSERT(menu_game_object != NULL, "Menu game object can't be NULL.");
	ASSERT(menu_image != NULL, "Menu image can't be NULL.");

	menu_game_object->AddComponent(*menu_image);
}



void Menu::Shutdown(){
	INFO("Destroying Menu.");
	DestroyComponents();
	DestroyGameObjects();
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

	audio_controller->Shutdown();
	free(audio_controller);
	audio_controller = NULL;
}

void Menu::DestroyGameObjects(){
	INFO("Destroying GameObjects.");
	free(menu_game_object);
	DEBUG("Freeing Menu pointer.");
	menu_game_object = NULL;
	DEBUG("Cleaning menu reference.");
}
