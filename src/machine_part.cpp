#include "machine_part.hpp"

using namespace Azo;

MachinePart::MachinePart(){}

MachinePart::MachinePart(std::string name, std::pair<double, double> position_relative_to_parent){
	m_name = name;
	m_position_relative_to_parent = position_relative_to_parent;
	m_current_position = position_relative_to_parent;
	CreateComponents();
}

void MachinePart::CreateComponents(){
	GenTurningAnimation();
	m_turning = new engine::Animation(*this, "sprites/machine_part.png", 1200.0f, m_turning_animation_sprites, 0, 23, true, 1);
	this->AddComponent(*m_turning);
}

void MachinePart::GenTurningAnimation(){
	for(int i = 0; i < 24; i++){
		m_turning_animation_sprites.push_back(new engine::Sprite());
	}

	m_turning_animation_sprites[0]->sprite_x = 13;
	m_turning_animation_sprites[0]->sprite_y = 11;
	m_turning_animation_sprites[0]->sprite_width = 49 - 13;
	m_turning_animation_sprites[0]->sprite_height = 47 - 11;

	m_turning_animation_sprites[1]->sprite_x = 50;
	m_turning_animation_sprites[1]->sprite_y = 11;
	m_turning_animation_sprites[1]->sprite_width = 86 - 50;
	m_turning_animation_sprites[1]->sprite_height = 47 - 11;

	m_turning_animation_sprites[2]->sprite_x = 87;
	m_turning_animation_sprites[2]->sprite_y = 11;
	m_turning_animation_sprites[2]->sprite_width = 123 - 87;
	m_turning_animation_sprites[2]->sprite_height = 47 - 11;

	m_turning_animation_sprites[3]->sprite_x = 124;
	m_turning_animation_sprites[3]->sprite_y = 11;
	m_turning_animation_sprites[3]->sprite_width = 160 - 124;
	m_turning_animation_sprites[3]->sprite_height = 47 - 11;

	m_turning_animation_sprites[4]->sprite_x = 161;
	m_turning_animation_sprites[4]->sprite_y = 11;
	m_turning_animation_sprites[4]->sprite_width = 197 - 161;
	m_turning_animation_sprites[4]->sprite_height = 47 - 11;

	m_turning_animation_sprites[5]->sprite_x = 198;
	m_turning_animation_sprites[5]->sprite_y = 11;
	m_turning_animation_sprites[5]->sprite_width = 234 - 198;
	m_turning_animation_sprites[5]->sprite_height = 47 - 11;

	m_turning_animation_sprites[6]->sprite_x = 240;
	m_turning_animation_sprites[6]->sprite_y = 11;
	m_turning_animation_sprites[6]->sprite_width = 271 - 240;
	m_turning_animation_sprites[6]->sprite_height = 47 - 11;

	m_turning_animation_sprites[7]->sprite_x = 277;
	m_turning_animation_sprites[7]->sprite_y = 11;
	m_turning_animation_sprites[7]->sprite_width = 308 - 277;
	m_turning_animation_sprites[7]->sprite_height = 47 - 11;

	m_turning_animation_sprites[8]->sprite_x = 314;
	m_turning_animation_sprites[8]->sprite_y = 11;
	m_turning_animation_sprites[8]->sprite_width = 345 - 314;
	m_turning_animation_sprites[8]->sprite_height = 47 - 11;

	m_turning_animation_sprites[9]->sprite_x = 351;
	m_turning_animation_sprites[9]->sprite_y = 11;
	m_turning_animation_sprites[9]->sprite_width = 382 - 351;
	m_turning_animation_sprites[9]->sprite_height = 47 - 11;

	m_turning_animation_sprites[10]->sprite_x = 388;
	m_turning_animation_sprites[10]->sprite_y = 11;
	m_turning_animation_sprites[10]->sprite_width = 419 - 388;
	m_turning_animation_sprites[10]->sprite_height = 47 - 11;

	m_turning_animation_sprites[11]->sprite_x = 425;
	m_turning_animation_sprites[11]->sprite_y = 11;
	m_turning_animation_sprites[11]->sprite_width = 456 - 425;
	m_turning_animation_sprites[11]->sprite_height = 47 - 11;

	m_turning_animation_sprites[12]->sprite_x = 461;
	m_turning_animation_sprites[12]->sprite_y = 11;
	m_turning_animation_sprites[12]->sprite_width = 497 - 461;
	m_turning_animation_sprites[12]->sprite_height = 47 - 11;

	m_turning_animation_sprites[13]->sprite_x = 461;
	m_turning_animation_sprites[13]->sprite_y = 11;
	m_turning_animation_sprites[13]->sprite_width = 497 - 461;
	m_turning_animation_sprites[13]->sprite_height = 47 - 11;

	m_turning_animation_sprites[14]->sprite_x = 461;
	m_turning_animation_sprites[14]->sprite_y = 11;
	m_turning_animation_sprites[14]->sprite_width = 497 - 461;
	m_turning_animation_sprites[14]->sprite_height = 47 - 11;

	m_turning_animation_sprites[15]->sprite_x = 461;
	m_turning_animation_sprites[15]->sprite_y = 11;
	m_turning_animation_sprites[15]->sprite_width = 497 - 461;
	m_turning_animation_sprites[15]->sprite_height = 47 - 11;

	m_turning_animation_sprites[16]->sprite_x = 461;
	m_turning_animation_sprites[16]->sprite_y = 11;
	m_turning_animation_sprites[16]->sprite_width = 497 - 461;
	m_turning_animation_sprites[16]->sprite_height = 47 - 11;

	m_turning_animation_sprites[17]->sprite_x = 461;
	m_turning_animation_sprites[17]->sprite_y = 11;
	m_turning_animation_sprites[17]->sprite_width = 497 - 461;
	m_turning_animation_sprites[17]->sprite_height = 47 - 11;

	m_turning_animation_sprites[18]->sprite_x = 689;
	m_turning_animation_sprites[18]->sprite_y = 11;
	m_turning_animation_sprites[18]->sprite_width = 720 - 689;
	m_turning_animation_sprites[18]->sprite_height = 47 - 11;

	m_turning_animation_sprites[19]->sprite_x = 726;
	m_turning_animation_sprites[19]->sprite_y = 11;
	m_turning_animation_sprites[19]->sprite_width = 757 - 726;
	m_turning_animation_sprites[19]->sprite_height = 47 - 11;

	m_turning_animation_sprites[20]->sprite_x = 763;
	m_turning_animation_sprites[20]->sprite_y = 11;
	m_turning_animation_sprites[20]->sprite_width = 794 - 763;
	m_turning_animation_sprites[20]->sprite_height = 47 - 11;

	m_turning_animation_sprites[21]->sprite_x = 800;
	m_turning_animation_sprites[21]->sprite_y = 11;
	m_turning_animation_sprites[21]->sprite_width = 831 - 800;
	m_turning_animation_sprites[21]->sprite_height = 47 - 11;

	m_turning_animation_sprites[22]->sprite_x = 837;
	m_turning_animation_sprites[22]->sprite_y = 11;
	m_turning_animation_sprites[22]->sprite_width = 868 - 837;
	m_turning_animation_sprites[22]->sprite_height = 47 - 11;

	m_turning_animation_sprites[23]->sprite_x = 874;
	m_turning_animation_sprites[23]->sprite_y = 11;
	m_turning_animation_sprites[23]->sprite_width = 905 - 874;
	m_turning_animation_sprites[23]->sprite_height = 47 - 11;

}