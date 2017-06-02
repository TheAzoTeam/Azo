#include "level_manager.hpp"
#include "game.hpp"

using namespace Azo;

LevelManager LevelManager::level_manager;

LevelManager::LevelManager(){}

void LevelManager::CreateMenu(){
	menu = new Menu("menu_scene");
}

void LevelManager::CreateLevelOne(){
	level_one = new LevelOne("level_one");
}

void LevelManager::GoToMenu(){
	CreateMenu();
	engine::Game::instance.AddScene(*menu);
	engine::Game::instance.ChangeScene("menu_scene");
}

void LevelManager::GoToLevelOne(){
	CreateLevelOne();
	engine::Game::instance.AddScene(*level_one);
	engine::Game::instance.ChangeScene("level_one");
}