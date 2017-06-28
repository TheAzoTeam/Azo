#include "level_one.hpp"

using namespace Azo;

LevelOne::LevelOne(){}

LevelOne::LevelOne(std::string name){
	this->scene_name = name;

	CreateGameObjects();
}

void LevelOne::CreateGameObjects(){
	DEBUG("Creating Level One Game Objects.");

	m_player = new Player("player", std::make_pair(0, 300));

	this->AddGameObject(*m_player);

	m_obstacle = new Obstacle("obstacle", std::make_pair(800, 300), ObstacleType::WESTERN_CAR);

	this->AddGameObject(*m_obstacle);

	for(auto each_block : m_obstacle->m_block_list){
		this->AddGameObject(*each_block);
	}

	m_ground = new Obstacle("ground", std::make_pair(0, 404.5), ObstacleType::GROUND);

	this->AddGameObject(*m_ground);

	m_level_one = new engine::GameObject("level_one", std::make_pair(0, 0));
	AddLevelParents();
	CreateLevelComponents();

	this->AddGameObject(*m_level_one);
}

void LevelOne::CreateLevelComponents(){
	DEBUG("Creating Level Components.");

	m_level_background = new engine::ImageComponent(*m_level_one, "backgrounds/level_one_part_one.png", 1);

	m_level_one->AddComponent(*m_level_background);

	m_audio_controller = new engine::AudioController();

	m_level_theme = new engine::AudioComponent(*m_level_one, "audios/tema_level_one.ogg", true, true);

	m_audio_controller->AddAudio("tema_level_one", *m_level_theme);

	m_level_one->AddComponent(*m_audio_controller);

	m_level_code = new LevelOneCode(*m_level_one);

	m_level_one->AddComponent(*m_level_code);
}

void LevelOne::AddLevelParents(){
	m_level_one->m_parent_list.push_back(m_player);
	m_level_one->m_parent_list.push_back(m_obstacle);
	m_level_one->m_parent_list.push_back(m_ground);
}
