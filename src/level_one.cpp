#include "level_one.hpp"

using namespace Azo;

LevelOne::LevelOne(){}

LevelOne::LevelOne(std::string name){
	this->scene_name = name;

	CreateGameObjects();
}

// Create new game objects for the level one here. Remember:
// the order used to add they to the scene is important.
void LevelOne::CreateGameObjects(){
	DEBUG("Creating Level One Game Objects.");

	DEBUG("Creating Player.");
	m_player = new Player("player", std::make_pair(0, 300));
	this->AddGameObject(*m_player);


	DEBUG("Creating ground.");
	m_ground = new Obstacle("ground", std::make_pair(0, 404.5), ObstacleType::GROUND);
	this->AddGameObject(*m_ground);


	DEBUG("Creating obstacle car 1.");
	m_obstacle_car_1 = new Obstacle("obstacle_car_1", std::make_pair(930, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_1);
	//TODO(Roger): Remove this. This is used to see the invisbile blocks.
	for(auto each_block : m_obstacle_car_1->m_block_list){
		this->AddGameObject(*each_block);
	}


	DEBUG("Creating part 1.");
	m_part_1 = new MachinePart("part_1", std::make_pair(1200, 120));
	this->AddGameObject(*m_part_1);


	DEBUG("Creating obstacle box 1.");
	m_obstacle_box_1 = new Obstacle("obstacle_box_1", std::make_pair(1300, 250), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_1);
	//TODO(Roger): Remove this. This is used to see the invisbile blocks.
	for(auto each_block : m_obstacle_box_1->m_block_list){
		this->AddGameObject(*each_block);
	}


	DEBUG("Creating level_one object.");
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

	m_level_theme = new engine::AudioComponent(*m_level_one, "audios/banjo.ogg", true, true);

	m_audio_controller->AddAudio("tema_level_one", *m_level_theme);

	m_level_one->AddComponent(*m_audio_controller);

	m_level_code = new LevelOneCode(*m_level_one);

	m_level_one->AddComponent(*m_level_code);
}

void LevelOne::AddLevelParents(){
	m_level_one->m_parent_list.push_back(m_player);
	m_level_one->m_parent_list.push_back(m_part_1);
	m_level_one->m_parent_list.push_back(m_obstacle_car_1);
	m_level_one->m_parent_list.push_back(m_obstacle_box_1);
	m_level_one->m_parent_list.push_back(m_ground);
}
