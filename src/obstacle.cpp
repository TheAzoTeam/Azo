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

void Obstacle::CreateComponents(){
	if(m_obstacle_type == ObstacleType::WESTERN_CAR){
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
		this->AddComponent(*m_obstacle_image);
	}
}

void Obstacle::CreateBlocks(){

	std::pair<double, double> block_position = m_position_relative_to_parent;
	if(m_obstacle_type == ObstacleType::GROUND){
		m_block_list.push_back(new InvisibleBlock("block_ground", block_position, std::make_pair(8192, 100)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_CAR){

		block_position.first += 59;
		block_position.second += 25;

		m_block_list.push_back(new InvisibleBlock("block_zero", block_position, std::make_pair(110, 64)));
	}

}
