#include "obstacle.hpp"

using namespace Azo;

Obstacle::Obstacle(){}

Obstacle::Obstacle(std::string name, std::pair<double, double> position_relative_to_parent, ObstacleType obstacle_type){
	m_name = name;
	m_position_relative_to_parent = position_relative_to_parent;
	m_current_position = m_position_relative_to_parent;

	m_obstacle_type = obstacle_type;

	CreateComponents();
	CreateBlocks();
}

// Here we add the imagens/sound to the obstacle, based on its type.
void Obstacle::CreateComponents(){
	DEBUG("Creating obstacle components.");
	if(m_obstacle_type == ObstacleType::WESTERN_CAR){
		DEBUG("Obstacle is a WESTERN CAR!");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
		this->AddComponent(*m_obstacle_image);
	}else if(m_obstacle_type == ObstacleType::WESTERN_BOX){
		DEBUG("Obstacle is a WESTERN BOX!");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/box.png", 1);
		this->AddComponent(*m_obstacle_image);
	}else if(m_obstacle_type == ObstacleType::WESTERN_ROCK){
		DEBUG("Obstacle is a WESTERN ROCK");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/rock.png", 1);
		this->AddComponent(*m_obstacle_image);
	}
}

// Here we create the invisible objects that make the obstacle.
// The name attribute of the InvisibleBlock isn't needed. It's for testing only.
// It's important to create the blocks based on the type of the object.
void Obstacle::CreateBlocks(){

	// We initialize the block' position as the position relative to parent of the obstacle.
	// This way we can position things inside the obstacle just by adding values.
	std::pair<double, double> block_position = m_position_relative_to_parent;

	if(m_obstacle_type == ObstacleType::GROUND){
		m_block_list.push_back(new InvisibleBlock("block_ground", block_position, std::make_pair(16384, 100)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_CAR){

		block_position.first += 59;
		block_position.second += 25;

		m_block_list.push_back(new InvisibleBlock("block_zero", block_position, std::make_pair(119, 139)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_BOX){
		block_position.first += 51;
		block_position.second += 9;

		m_block_list.push_back(new InvisibleBlock("block_two", block_position, std::make_pair(70, 68)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_ROCK){
		block_position.first += 36;
		block_position.second += 3;

		m_block_list.push_back(new InvisibleBlock("block_two", block_position, std::make_pair(100, 101)));
	}

}
