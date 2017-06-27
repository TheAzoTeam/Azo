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

	block_position.first += 43;
	block_position.second += 28;

	m_block_list.push_back(new InvisibleBlock(block_position, std::make_pair(14, 64)));

	// Since the position is on left, we just need to  add the previous object size to get to the left
	// Of the next block.

	block_position.first += 14;

	m_block_list.push_back(new InvisibleBlock(block_position, std::make_pair(58, 91)));

	block_position.first += 58;

	m_block_list.push_back(new InvisibleBlock(block_position, std::make_pair(15, 66)));

}
