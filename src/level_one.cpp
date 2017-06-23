#include "level_one.hpp"

using namespace Azo;

LevelOne::LevelOne(){}

LevelOne::LevelOne(std::string name){
	this->scene_name = name;

	CreateGameObjects();
}

void LevelOne::CreateGameObjects(){
	DEBUG("Creating Level One Game Objects.");

	m_level_one = new engine::GameObject("level_one", std::make_pair(0, 0));

	this->AddGameObject(*m_level_one);

	m_player = new Player("player", std::make_pair(300, 300));

	this->AddGameObject(*m_player);
}

