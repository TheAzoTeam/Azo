#include "obstacle.hpp"

using namespace Azo;

Obstacle::Obstacle(){}

Obstacle::Obstacle(std::string name, std::pair<double, double> position_relative_to_parent){
	m_name = name;
	m_position_relative_to_parent = position_relative_to_parent;

	m_current_position = m_position_relative_to_parent;

	CreateComponents();
}

void Obstacle::CreateComponents(){
	m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
	this->AddComponent(*m_obstacle_image);
}
