#include "obstacle.hpp"

using namespace Azo;

Obstacle::Obstacle(){}

Obstacle::Obstacle(std::string name, std::pair<double, double> position_relative_to_parent){
	m_name = name;
	m_position_relative_to_parent = position_relative_to_parent;

	m_current_position = m_position_relative_to_parent;

	CreateComponents();
	CreateBlocks();
}

void Obstacle::CreateComponents(){
	m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
	this->AddComponent(*m_obstacle_image);
}

void Obstacle::CreateBlocks(){
	std::pair<double, double> block_position = m_current_position;

	block_position.first += 59;
	block_position.second += 25;

	m_block_list.push_back(new InvisibleBlock("block_zero", block_position, std::make_pair(110, 64)));

}
