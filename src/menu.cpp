#include "menu.hpp"

using namespace Azo;

Menu::Menu(std::string name){
	this->scene_name = name;
	CreateGameObjects();
}

void Menu::CreateGameObjects(){
	DEBUG("Creating Menu GameObjects.");

	m_menu = new engine::GameObject("menu", std::make_pair(0, 0));
	CreateMenuComponents();

	this->AddGameObject(*m_menu);
}

void Menu::CreateMenuComponents(){
	m_background = new engine::BackgroundComponent(*m_menu, "backgrounds/menu.png");
	m_menu->AddComponent(*m_background);
	m_code = new MenuCode(m_menu);
	m_menu->AddComponent(*m_code);
}