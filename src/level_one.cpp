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

	DEBUG("Creating ground.");
	m_ground = new Obstacle("ground", std::make_pair(0, 404.5), ObstacleType::GROUND);
	this->AddGameObject(*m_ground);


	DEBUG("Creating obstacle car 1.");
	m_obstacle_car_1 = new Obstacle("obstacle_car_1", std::make_pair(1135, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_1);


	DEBUG("Creating obstacle aerial 1.");
	m_obstacle_aerial_1 = new Obstacle("obstacle_aerial_1", std::make_pair(1320, 250), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_1);


	DEBUG("Creating part 1.");
	m_part_1 = new MachinePart("part_1", std::make_pair(1570, 100));
	this->AddGameObject(*m_part_1);

	DEBUG("Creating part 1.");
	m_part_2 = new MachinePart("part_2", std::make_pair(1650, 150));
	this->AddGameObject(*m_part_2);

	DEBUG("Creating obstacle aerial 2.");
	m_obstacle_aerial_2 = new Obstacle("obstacle_aerial_2", std::make_pair(1735, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_2);


	DEBUG("Creating obstacle aerial 3.");
	m_obstacle_aerial_3 = new Obstacle("obstacle_aerial_3", std::make_pair(1900, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_3);


	DEBUG("Creating part 2.");
	m_part_2 = new MachinePart("part_2", std::make_pair(2250, 200));
	this->AddGameObject(*m_part_2);


	DEBUG("Creating obstacle box 1.");
	m_obstacle_box_1 = new Obstacle("obstacle_box_1", std::make_pair(2200, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_1);


	DEBUG("Creating obstacle box 2.");
	m_obstacle_box_2 = new Obstacle("obstacle_box_2", std::make_pair(2600, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_2);


	DEBUG("Creating obstacle aerial 4.");
	m_obstacle_aerial_4 = new Obstacle("obstacle_aerial_4", std::make_pair(2710, 230), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_4);


	DEBUG("Creating part 3.")
	m_part_3 = new MachinePart("part_3", std::make_pair(2790, 100));
	this->AddGameObject(*m_part_3);


	DEBUG("Creating part 4.")
	m_part_4 = new MachinePart("part_4", std::make_pair(2900, 310));
	this->AddGameObject(*m_part_4);


	DEBUG("Creating part 5.")
	m_part_5 = new MachinePart("part_5", std::make_pair(2950, 310));
	this->AddGameObject(*m_part_5);


	DEBUG("Creating Player.");
	m_player = new Player("player", std::make_pair(0, 300));
	this->AddGameObject(*m_player);


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
	DEBUG("Adding level parents.");

	m_level_one->m_parent_list.push_back(m_obstacle_car_1);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_1);
	m_level_one->m_parent_list.push_back(m_part_1);
	m_level_one->m_parent_list.push_back(m_part_2);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_2);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_3);
	m_level_one->m_parent_list.push_back(m_part_2);
	m_level_one->m_parent_list.push_back(m_obstacle_box_1);
	m_level_one->m_parent_list.push_back(m_obstacle_box_2);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_4);
	m_level_one->m_parent_list.push_back(m_part_3);
	m_level_one->m_parent_list.push_back(m_part_4);
	m_level_one->m_parent_list.push_back(m_part_5);
	m_level_one->m_parent_list.push_back(m_player);
	m_level_one->m_parent_list.push_back(m_ground);
}
