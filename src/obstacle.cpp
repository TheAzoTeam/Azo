#include "obstacle.hpp"

using namespace Azo;

Obstacle::Obstacle(){}

Obstacle::~Obstacle(){}

void Obstacle::shutdown(){
	for(auto each_block : m_block_list){
		if(each_block != NULL){
			each_block->shutdown();
			delete(each_block);
			each_block = NULL;
		}
	}

	if(m_turning_animation_sprites.size() > 0){
		for(auto each_animation : m_turning_animation_sprites){
			if(each_animation != NULL){
				delete(each_animation);
				each_animation = NULL;
			}
		}
	}

	if(m_obstacle_image != NULL){
		delete(m_obstacle_image);
		m_obstacle_image = NULL;
	}

	if(m_audio_controller != NULL){
		m_audio_controller->shutdown();
		delete(m_audio_controller);
		m_audio_controller = NULL;
	}

	if(m_collected != NULL){
		m_collected = NULL;
	}

	if(m_turning != NULL){
		delete(m_turning);
		m_turning = NULL;
	}


	if(m_machine_part_code != NULL){
		m_machine_part_code->shutdown();
		delete(m_machine_part_code);
		m_machine_part_code = NULL;
	}
}


Obstacle::Obstacle(std::string name, std::pair<double, double> position_relative_to_parent, ObstacleType obstacle_type){
	mName = name;
	m_position_relative_to_parent = position_relative_to_parent;
	mCurrentPosition = m_position_relative_to_parent;

	m_obstacle_type = obstacle_type;

	CreateComponents();
}

// Here we add the imagens/sound to the obstacle, based on its type.
void Obstacle::CreateComponents(){
	DEBUG("Creating obstacle components.");
	if(m_obstacle_type == ObstacleType::WESTERN_CAR){
		DEBUG("Obstacle is a WESTERN CAR!");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
		this->addComponent(*m_obstacle_image);
		CreateBlocks();

	}else if(m_obstacle_type == ObstacleType::WESTERN_BOX){
		DEBUG("Obstacle is a WESTERN BOX!");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/box.png", 1);
		this->addComponent(*m_obstacle_image);
		CreateBlocks();

	}else if(m_obstacle_type == ObstacleType::WESTERN_RAISED_BOX){
		DEBUG("Obstacle is a WESTERN RAISED BOX!");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/raised_box.png", 1);
		this->addComponent(*m_obstacle_image);
		CreateBlocks();

	}else if(m_obstacle_type == ObstacleType::WESTERN_ROCK){
		DEBUG("Obstacle is a WESTERN ROCK");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/rock.png", 1);
		this->addComponent(*m_obstacle_image);
		CreateBlocks();

	}else if(m_obstacle_type == ObstacleType::MACHINE_PART){
		DEBUG("Obstacle is a MACHINE PART");
		m_machine_part_state = MachinePartState::NON_COLLECTED;
		GenTurningAnimation();
		m_turning = new engine::Animation(*this, "sprites/machine_part.png", 1200.0f, m_turning_animation_sprites, 0, 23, true, 1);
		this->addComponent(*m_turning);

		m_audio_controller = new engine::AudioController();
		m_collected = new engine::AudioComponent(*this, "audios/coleta.ogg", false, false);
		m_audio_controller->AddAudio("coleta", *m_collected);
		this->addComponent(*m_audio_controller);

		m_machine_part_code = new MachinePartCode(this);
		this->addComponent(*m_machine_part_code);

	}else if(m_obstacle_type == ObstacleType::WESTERN_SPIKE){
		DEBUG("Obstacle is a WESTERN SPIKE");

		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/Espinhos_rose.png", 1);
		this->addComponent(*m_obstacle_image);
		CreateBlocks();
	}else if(m_obstacle_type == ObstacleType::WESTERN_POST){
		DEBUG("Obstacle is a WESTERN POST");

		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/obstaculoDescer2.png", 1);
		this->addComponent(*m_obstacle_image);
		CreateBlocks();
	}else if(m_obstacle_type == ObstacleType::GROUND){
		CreateBlocks();
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
		//	DEBUG("Creating invisible block for the ground.");
		m_block_list.push_back(new InvisibleBlock("block_1", block_position, std::make_pair(21000, 100)));
		//	DEBUG("List size: " << m_block_list.size());
	}else if(m_obstacle_type == ObstacleType::WESTERN_CAR){

		block_position.first += 69;
		block_position.second += 20;

		m_block_list.push_back(new InvisibleBlock("block_2", block_position, std::make_pair(109, 143)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_BOX){
		block_position.first += 58;
		block_position.second += 6;

		m_block_list.push_back(new InvisibleBlock("block_3", block_position, std::make_pair(63, 73)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_RAISED_BOX){
		block_position.first += 35;
		block_position.second += 6;

		m_block_list.push_back(new InvisibleBlock("block_4", block_position, std::make_pair(50, 68)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_ROCK){
		block_position.first += 80;
		block_position.second += 12;

		m_block_list.push_back(new InvisibleBlock("block_5", block_position, std::make_pair(4, 100)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_SPIKE){
		block_position.first += 19;
		block_position.second += 23;

		m_block_list.push_back(new InvisibleBlock("block_6", block_position, std::make_pair(210, 92)));
	}else if(m_obstacle_type == ObstacleType::WESTERN_POST){
		block_position.first += 48;
		block_position.second += 32;

		m_block_list.push_back(new InvisibleBlock("block_7", block_position, std::make_pair(23, 106)));
	}

}

void Obstacle::GenTurningAnimation(){
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
