// TODO(Roger): Change all game objects (except menu_game_object) to components.
//menu_game_object->AddComponent(*menu_theme);


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

	CreateImageComponents();
	SetImageComponents();

	CreateAudioComponents();
	SetAudioComponents();

	CreateBackgroundComponents();
	SetBackgroundComponents();

	CreateCodeComponents();
	SetCodeComponents();

	SetGameObjects();
}

void Menu::CreateGameObjects(){
	disable_sound_button = new engine::GameObject("disable_sound_button", 0, 500);
	play_button_menu = new engine::GameObject("play_button_menu", 300, 300);
	menu_game_object = new engine::GameObject("menu_game_object", 0, 0);
}

void Menu::CreateImageComponents(){
	DEBUG("Creating Image Components");
	disable_sound_image = new engine::ImageComponent(*disable_sound_button, "general_images/disable_sound.png");
	play_button_image = new engine::ImageComponent(*play_button_menu, "backgrounds/play_button.png");
}

void Menu::CreateBackgroundComponents(){
	DEBUG("Creating Background Components");

	menu_image = new engine::BackgroundComponent(*menu_game_object, "backgrounds/menu.png");
}

void Menu::CreateCodeComponents(){
	DEBUG("Creating Code Components");

	disable_sound_code = new DisableSoundCode(*disable_sound_button);
	menu_code = new MenuCode(*menu_game_object);
}

void Menu::SetCodeComponents(){
	DEBUG("Setting Code Components");

	ASSERT(menu_code != NULL, "Menu Code can't be NULL.");
	ASSERT(disable_sound_code != NULL, "Disable Sound Code can't be NULL.");

	menu_game_object->AddComponent(*menu_code);
	disable_sound_button->AddComponent(*disable_sound_code);
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
	ASSERT(disable_sound_button != NULL, "Disable Sound button can't be NULL");
	ASSERT(audio_controller != NULL, "Audio controller can't be null");

	audio_controller->AddAudio("menu_theme", *menu_theme);
	disable_sound_button->AddComponent(*audio_controller);
}

void Menu::SetGameObjects(){
	DEBUG("Setting Menu Game Objects");
	ASSERT(play_button_menu != NULL, "Play button menu can't be NULL.");
	ASSERT(menu_game_object != NULL, "Menu game object can't be NULL.");
	ASSERT(disable_sound_button != NULL, "Disable sound button can't be NULL.");

	this->AddGameObject(*disable_sound_button);
	this->AddGameObject(*play_button_menu);
	this->AddGameObject(*menu_game_object);
}

void Menu::SetImageComponents(){
	DEBUG("Setting Image Components");

	ASSERT(play_button_menu != NULL, "Play button menu can't be NULL.");
	ASSERT(play_button_image != NULL, "Play button image object can't be NULL.");
	ASSERT(disable_sound_image != NULL, "Disable Sound Image can't be NULL.");

	play_button_menu->AddComponent(*play_button_image);
	disable_sound_button->AddComponent(*disable_sound_image);
}
void Menu::SetBackgroundComponents(){
	DEBUG("Setting Background Components");

	ASSERT(menu_game_object != NULL, "Menu game object can't be NULL.");
	ASSERT(menu_image != NULL, "Menu image can't be NULL.");

	menu_game_object->AddComponent(*menu_image);
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

	menu_theme->Shutdown();
	free(menu_theme);
	menu_theme = NULL;
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
