#include "level_one.hpp"

using namespace Azo;

LevelOne::LevelOne(){}

LevelOne::LevelOne(std::string name){
	this->scene_name = name;

	CreateGameObjects();
}

void LevelOne::Restart(){
	game_object_map.clear();

	//TODO(Roger): Add objects to be recreated one by one, here, instead of recalling CreateGameObjects.
	CreateGameObjects();

}

// Create new game objects for the level one here. Remember:
// the order used to add they to the scene is important.
void LevelOne::CreateGameObjects(){
	DEBUG("Creating Level One Game Objects.");

	DEBUG("Creating level_one object.");
	m_level_one = new engine::GameObject("level_one", std::make_pair(0, 0));

	m_level_background_1 = new engine::ImageComponent(*m_level_one, "backgrounds/level_one_part_one.png", 1);
	m_level_one->AddComponent(*m_level_background_1);

	m_level_background_2 = new engine::ImageComponent(*m_level_one, "backgrounds/level_one_part_two.png", 1, std::make_pair(8188, 0));
	m_level_one->AddComponent(*m_level_background_2);

	m_level_background_3 = new engine::ImageComponent(*m_level_one, "backgrounds/level_one_part_three.png", 1, std::make_pair(16379, 0));
	m_level_one->AddComponent(*m_level_background_3);

	m_audio_controller = new engine::AudioController();
	m_level_theme = new engine::AudioComponent(*m_level_one, "audios/banjo.ogg", true, true);
	m_audio_controller->AddAudio("tema_level_one", *m_level_theme);
	m_level_one->AddComponent(*m_audio_controller);

	this->AddGameObject(*m_level_one);



	DEBUG("Creating ground.");
	m_ground = new Obstacle("ground", std::make_pair(0, 404.5), ObstacleType::GROUND);
	this->AddGameObject(*m_ground);


	DEBUG("Creating post 1");
	m_post_1 = new Obstacle("obstacle_post_1", std::make_pair(850, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_post_1);


	DEBUG("Creating obstacle car 1.");
	m_obstacle_car_1 = new Obstacle("obstacle_car_1", std::make_pair(1135, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_1);


	DEBUG("Creating spike 1.");
	m_spike_1 = new Obstacle("obstacle_spike_1", std::make_pair(1349, 340), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_1);


	DEBUG("Creating obstacle box 0_1.");
	m_obstacle_box_0_1 = new Obstacle("obstacle_box_0_1", std::make_pair(1309, 310), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_0_1);


	DEBUG("Creating obstacle aerial 1.");
	m_obstacle_aerial_1 = new Obstacle("obstacle_aerial_1", std::make_pair(1350, 250), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_1);


	DEBUG("Creating part 1.");
	m_part_1 = new Obstacle("part_1", std::make_pair(1500, 80), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_1);


	DEBUG("Creating obstacle aerial 2.");
	m_obstacle_aerial_2 = new Obstacle("obstacle_aerial_2", std::make_pair(1755, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_2);


	DEBUG("Creating part 1_1.");
	m_part_1_1 = new Obstacle("part_1_1", std::make_pair(1890, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_1_1);


	DEBUG("Creating obstacle aerial 3.");
	m_obstacle_aerial_3 = new Obstacle("obstacle_aerial_3", std::make_pair(2030, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_3);


	DEBUG("Creating part 2.");
	m_part_2 = new Obstacle("part_2", std::make_pair(2225, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_2);


	DEBUG("Creating obstacle box 1.");
	m_obstacle_box_1 = new Obstacle("obstacle_box_1", std::make_pair(2225, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_1);


	DEBUG("Creating obstacle box 2.");
	m_obstacle_box_2 = new Obstacle("obstacle_box_2", std::make_pair(2645, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_2);


	DEBUG("Creating obstacle box 2_1.");
	m_obstacle_box_2_1 = new Obstacle("obstacle_box_2_1", std::make_pair(2779, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_2_1);


	DEBUG("Creating obstacle aerial 4.");
	m_obstacle_aerial_4 = new Obstacle("obstacle_aerial_4", std::make_pair(2820, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_4);


	DEBUG("Creating part 3.")
	m_part_3 = new Obstacle("part_3", std::make_pair(2975, 310), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_3);


	DEBUG("Creating obstacle car 2.");
	m_obstacle_car_2 = new Obstacle("obstacle_car_2", std::make_pair(3040, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_2);


	DEBUG("Creating part 4.");
	m_part_4 = new Obstacle("part_4", std::make_pair(3285, 100), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_4);


	DEBUG("Creating obstacle aerial 5.");
	m_obstacle_aerial_5 = new Obstacle("obstacle_aerial_5", std::make_pair(3510, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_5);


	DEBUG("Creating part 4_1.");
	m_part_4_1 = new Obstacle("part_4_1", std::make_pair(3655, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_4_1);


	DEBUG("Creating obstacle aerial 6.");
	m_obstacle_aerial_6 = new Obstacle("obstacle_aerial_6", std::make_pair(3675, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_6);


	DEBUG("Creating part 5.");
	m_part_5 = new Obstacle("part_5", std::make_pair(3975, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_5);


	DEBUG("Creating obstacle box 3.");
	m_obstacle_box_3 = new Obstacle("obstacle_box_3", std::make_pair(3975, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_3);


	DEBUG("Creating obstacle rock 1");
	m_obstacle_rock_1 = new Obstacle("obstacle_rock_1", std::make_pair(4300, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_1);


	DEBUG("Creating part 6.");
	m_part_6 = new Obstacle("part_6", std::make_pair(4460, 350), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_6);


	DEBUG("Creating obstacle aerial 7.");
	m_obstacle_aerial_7 = new Obstacle("obstacle_aerial_7", std::make_pair(4660, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_7);


	DEBUG("Creating obstacle rock 2");
	m_obstacle_rock_2 = new Obstacle("obstacle_rock_2", std::make_pair(4855, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_2);


	DEBUG("Creating part 7.");
	m_part_7 = new Obstacle("part_7", std::make_pair(5015, 350), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_7);


	DEBUG("Creating obstacle aerial 8.");
	m_obstacle_aerial_8 = new Obstacle("obstacle_aerial_8", std::make_pair(5215, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_8);


	DEBUG("Creating part 7_1.");
	m_part_7_1 = new Obstacle("part_7_1", std::make_pair(5360, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_7_1);


	DEBUG("Creating obstacle aerial 9.");
	m_obstacle_aerial_9 = new Obstacle("obstacle_aerial_9", std::make_pair(5380, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_9);


	DEBUG("Creating part 8.");
	m_part_8 = new Obstacle("part_8", std::make_pair(5570, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_8);


	DEBUG("Creating part 9.");
	m_part_9 = new Obstacle("part_9", std::make_pair(6100, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_9);


	DEBUG("Creating obstacle aerial 10.");
	m_obstacle_aerial_10 = new Obstacle("obstacle_aerial_10", std::make_pair(6150, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_10);


	DEBUG("Creating part 10.");
	m_part_10 = new Obstacle("part_10", std::make_pair(6340, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_10);


	DEBUG("Creating obstacle car 3.");
	m_obstacle_car_3 = new Obstacle("obstacle_car_3", std::make_pair(6700, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_3);


	DEBUG("Creating part 11.");
	m_part_11 = new Obstacle("part_11", std::make_pair(6880, 80), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_11);


	DEBUG("Creating obstacle aerial 11.");
	m_obstacle_aerial_11 = new Obstacle("obstacle_aerial_11", std::make_pair(7000, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_11);


	DEBUG("Creating part 12.");
	m_part_12 = new Obstacle("part_12", std::make_pair(7145, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_12);


	DEBUG("Creating obstacle aerial 12.");
	m_obstacle_aerial_12 = new Obstacle("obstacle_aerial_12", std::make_pair(7165, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_12);


	DEBUG("Creating part 13.");
	m_part_13 = new Obstacle("part_13", std::make_pair(7540, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_13);


	DEBUG("Creating part 14.");
	m_part_14 = new Obstacle("part_14", std::make_pair(7830, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_14);


	DEBUG("Creating part 15.");
	m_part_15 = new Obstacle("part_15", std::make_pair(8040, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_15);


	DEBUG("Creating part 16.");
	m_part_16 = new Obstacle("part_16", std::make_pair(8390, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_16);


	DEBUG("Creating obstacle aerial 13.");
	m_obstacle_aerial_13 = new Obstacle("obstacle_aerial_13", std::make_pair(8570, 245), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_aerial_13);


	DEBUG("Creating spike 2.");
	m_spike_2 = new Obstacle("obstacle_spike_2", std::make_pair(8880, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_2);


	DEBUG("Creating obstacle box 4.");
	m_obstacle_box_4 = new Obstacle("obstacle_box_4", std::make_pair(8820, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_4);


	DEBUG("Creating spike 3.");
	m_spike_3 = new Obstacle("obstacle_spike_3", std::make_pair(9120, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_3);


	DEBUG("Creating obstacle box 5.");
	m_obstacle_box_5 = new Obstacle("obstacle_box_5", std::make_pair(9117, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_box_5);


	DEBUG("Creating spike 4.");
	m_spike_4 = new Obstacle("obstacle_spike_4", std::make_pair(9360, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_4);


	DEBUG("Creating obstacle box 6.");
	m_obstacle_box_6 = new Obstacle("obstacle_box_6", std::make_pair(9358, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_box_6);


	DEBUG("Creating obstacle aerial 14.");
	m_obstacle_aerial_14 = new Obstacle("obstacle_aerial_14", std::make_pair(9358, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_14);


	DEBUG("Creating obstacle box 7.");
	m_obstacle_box_7 = new Obstacle("obstacle_box_7", std::make_pair(9599, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_box_7);


	DEBUG("Creating obstacle aerial 15.");
	m_obstacle_aerial_15 = new Obstacle("obstacle_aerial_15", std::make_pair(9599, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_15);








	DEBUG("Creating Player.");
	m_player = new Player("player", std::make_pair(165, 300));
	this->AddGameObject(*m_player);


	AddLevelParents();

	m_level_code = new LevelOneCode(*m_level_one);
	m_level_one->AddComponent(*m_level_code);

}

void LevelOne::AddLevelParents(){
	DEBUG("Adding level parents.");

	m_level_one->m_parent_list.push_back(m_post_1);
	m_level_one->m_parent_list.push_back(m_obstacle_car_1);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_1);
	m_level_one->m_parent_list.push_back(m_obstacle_box_0_1);
	m_level_one->m_parent_list.push_back(m_spike_1);
	m_level_one->m_parent_list.push_back(m_part_1);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_2);
	m_level_one->m_parent_list.push_back(m_part_1_1);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_3);
	m_level_one->m_parent_list.push_back(m_part_2);
	m_level_one->m_parent_list.push_back(m_obstacle_box_1);
	m_level_one->m_parent_list.push_back(m_obstacle_box_2);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_4);
	m_level_one->m_parent_list.push_back(m_obstacle_box_2_1);
	m_level_one->m_parent_list.push_back(m_part_3);
	m_level_one->m_parent_list.push_back(m_obstacle_car_2);
	m_level_one->m_parent_list.push_back(m_part_4);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_5);
	m_level_one->m_parent_list.push_back(m_part_4_1);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_6);
	m_level_one->m_parent_list.push_back(m_part_5);
	m_level_one->m_parent_list.push_back(m_obstacle_box_3);
	m_level_one->m_parent_list.push_back(m_obstacle_rock_1);
	m_level_one->m_parent_list.push_back(m_part_6);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_7);
	m_level_one->m_parent_list.push_back(m_obstacle_rock_2);
	m_level_one->m_parent_list.push_back(m_part_7);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_8);
	m_level_one->m_parent_list.push_back(m_part_7_1);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_9);
	m_level_one->m_parent_list.push_back(m_part_8);
	m_level_one->m_parent_list.push_back(m_part_9);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_10);
	m_level_one->m_parent_list.push_back(m_part_10);
	m_level_one->m_parent_list.push_back(m_obstacle_car_3);
	m_level_one->m_parent_list.push_back(m_part_11);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_11);
	m_level_one->m_parent_list.push_back(m_part_12);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_12);
	m_level_one->m_parent_list.push_back(m_part_13);
	m_level_one->m_parent_list.push_back(m_part_14);
	m_level_one->m_parent_list.push_back(m_part_15);
	m_level_one->m_parent_list.push_back(m_part_16);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_13);
	m_level_one->m_parent_list.push_back(m_spike_2);
	m_level_one->m_parent_list.push_back(m_obstacle_box_4);
	m_level_one->m_parent_list.push_back(m_spike_3);
	m_level_one->m_parent_list.push_back(m_obstacle_box_5);
	m_level_one->m_parent_list.push_back(m_spike_4);
	m_level_one->m_parent_list.push_back(m_obstacle_box_6);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_14);
	m_level_one->m_parent_list.push_back(m_obstacle_box_7);
	m_level_one->m_parent_list.push_back(m_obstacle_aerial_15);
	m_level_one->m_parent_list.push_back(m_player);
	m_level_one->m_parent_list.push_back(m_ground);
}
