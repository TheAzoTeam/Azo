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
		for(auto eachAnimation : m_turning_animation_sprites){
			if(eachAnimation != NULL){
				delete(eachAnimation);
				eachAnimation = NULL;
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
	m_name = name;
	m_position_relative_to_parent = position_relative_to_parent;
	m_current_position = m_position_relative_to_parent;

	m_obstacle_type = obstacle_type;

	CreateComponents();
}

// Here we add the imagens/sound to the obstacle, based on its type.
void Obstacle::CreateComponents(){
	DEBUG("Creating obstacle components.");
	if(m_obstacle_type == ObstacleType::WESTERN_CAR){
		DEBUG("Obstacle is a WESTERN CAR!");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
		this->AddComponent(*m_obstacle_image);
		CreateBlocks();

	}else if(m_obstacle_type == ObstacleType::WESTERN_BOX){
		DEBUG("Obstacle is a WESTERN BOX!");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/box.png", 1);
		this->AddComponent(*m_obstacle_image);
		CreateBlocks();

	}else if(m_obstacle_type == ObstacleType::WESTERN_RAISED_BOX){
		DEBUG("Obstacle is a WESTERN RAISED BOX!");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/raised_box.png", 1);
		this->AddComponent(*m_obstacle_image);
		CreateBlocks();

	}else if(m_obstacle_type == ObstacleType::WESTERN_ROCK){
		DEBUG("Obstacle is a WESTERN ROCK");
		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/rock.png", 1);
		this->AddComponent(*m_obstacle_image);
		CreateBlocks();

	}else if(m_obstacle_type == ObstacleType::MACHINE_PART){
		DEBUG("Obstacle is a MACHINE PART");
		m_machine_part_state = MachinePartState::NON_COLLECTED;
		GenTurningAnimation();
		m_turning = new engine::Animation(*this, "sprites/machine_part.png", 1200.0f, m_turning_animation_sprites, 0, 23, true, 1);
		this->AddComponent(*m_turning);

		m_audio_controller = new engine::AudioController();
		m_collected = new engine::AudioComponent(*this, "audios/coleta.ogg", false, false);
		m_audio_controller->AddAudio("coleta", *m_collected);
		this->AddComponent(*m_audio_controller);

		m_machine_part_code = new MachinePartCode(this);
		this->AddComponent(*m_machine_part_code);

	}else if(m_obstacle_type == ObstacleType::WESTERN_SPIKE){
		DEBUG("Obstacle is a WESTERN SPIKE");

		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/Espinhos_rose.png", 1);
		this->AddComponent(*m_obstacle_image);
		CreateBlocks();
	}else if(m_obstacle_type == ObstacleType::WESTERN_POST){
		DEBUG("Obstacle is a WESTERN POST");

		m_obstacle_image = new engine::ImageComponent(*this, "backgrounds/obstaculoDescer2.png", 1);
		this->AddComponent(*m_obstacle_image);
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

	m_turning_animation_sprites[0]->spriteX = 13;
	m_turning_animation_sprites[0]->spriteY = 11;
	m_turning_animation_sprites[0]->spriteWidth = 49 - 13;
	m_turning_animation_sprites[0]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[1]->spriteX = 50;
	m_turning_animation_sprites[1]->spriteY = 11;
	m_turning_animation_sprites[1]->spriteWidth = 86 - 50;
	m_turning_animation_sprites[1]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[2]->spriteX = 87;
	m_turning_animation_sprites[2]->spriteY = 11;
	m_turning_animation_sprites[2]->spriteWidth = 123 - 87;
	m_turning_animation_sprites[2]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[3]->spriteX = 124;
	m_turning_animation_sprites[3]->spriteY = 11;
	m_turning_animation_sprites[3]->spriteWidth = 160 - 124;
	m_turning_animation_sprites[3]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[4]->spriteX = 161;
	m_turning_animation_sprites[4]->spriteY = 11;
	m_turning_animation_sprites[4]->spriteWidth = 197 - 161;
	m_turning_animation_sprites[4]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[5]->spriteX = 198;
	m_turning_animation_sprites[5]->spriteY = 11;
	m_turning_animation_sprites[5]->spriteWidth = 234 - 198;
	m_turning_animation_sprites[5]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[6]->spriteX = 240;
	m_turning_animation_sprites[6]->spriteY = 11;
	m_turning_animation_sprites[6]->spriteWidth = 271 - 240;
	m_turning_animation_sprites[6]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[7]->spriteX = 277;
	m_turning_animation_sprites[7]->spriteY = 11;
	m_turning_animation_sprites[7]->spriteWidth = 308 - 277;
	m_turning_animation_sprites[7]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[8]->spriteX = 314;
	m_turning_animation_sprites[8]->spriteY = 11;
	m_turning_animation_sprites[8]->spriteWidth = 345 - 314;
	m_turning_animation_sprites[8]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[9]->spriteX = 351;
	m_turning_animation_sprites[9]->spriteY = 11;
	m_turning_animation_sprites[9]->spriteWidth = 382 - 351;
	m_turning_animation_sprites[9]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[10]->spriteX = 388;
	m_turning_animation_sprites[10]->spriteY = 11;
	m_turning_animation_sprites[10]->spriteWidth = 419 - 388;
	m_turning_animation_sprites[10]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[11]->spriteX = 425;
	m_turning_animation_sprites[11]->spriteY = 11;
	m_turning_animation_sprites[11]->spriteWidth = 456 - 425;
	m_turning_animation_sprites[11]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[12]->spriteX = 461;
	m_turning_animation_sprites[12]->spriteY = 11;
	m_turning_animation_sprites[12]->spriteWidth = 497 - 461;
	m_turning_animation_sprites[12]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[13]->spriteX = 461;
	m_turning_animation_sprites[13]->spriteY = 11;
	m_turning_animation_sprites[13]->spriteWidth = 497 - 461;
	m_turning_animation_sprites[13]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[14]->spriteX = 461;
	m_turning_animation_sprites[14]->spriteY = 11;
	m_turning_animation_sprites[14]->spriteWidth = 497 - 461;
	m_turning_animation_sprites[14]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[15]->spriteX = 461;
	m_turning_animation_sprites[15]->spriteY = 11;
	m_turning_animation_sprites[15]->spriteWidth = 497 - 461;
	m_turning_animation_sprites[15]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[16]->spriteX = 461;
	m_turning_animation_sprites[16]->spriteY = 11;
	m_turning_animation_sprites[16]->spriteWidth = 497 - 461;
	m_turning_animation_sprites[16]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[17]->spriteX = 461;
	m_turning_animation_sprites[17]->spriteY = 11;
	m_turning_animation_sprites[17]->spriteWidth = 497 - 461;
	m_turning_animation_sprites[17]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[18]->spriteX = 689;
	m_turning_animation_sprites[18]->spriteY = 11;
	m_turning_animation_sprites[18]->spriteWidth = 720 - 689;
	m_turning_animation_sprites[18]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[19]->spriteX = 726;
	m_turning_animation_sprites[19]->spriteY = 11;
	m_turning_animation_sprites[19]->spriteWidth = 757 - 726;
	m_turning_animation_sprites[19]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[20]->spriteX = 763;
	m_turning_animation_sprites[20]->spriteY = 11;
	m_turning_animation_sprites[20]->spriteWidth = 794 - 763;
	m_turning_animation_sprites[20]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[21]->spriteX = 800;
	m_turning_animation_sprites[21]->spriteY = 11;
	m_turning_animation_sprites[21]->spriteWidth = 831 - 800;
	m_turning_animation_sprites[21]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[22]->spriteX = 837;
	m_turning_animation_sprites[22]->spriteY = 11;
	m_turning_animation_sprites[22]->spriteWidth = 868 - 837;
	m_turning_animation_sprites[22]->spriteHeight = 47 - 11;

	m_turning_animation_sprites[23]->spriteX = 874;
	m_turning_animation_sprites[23]->spriteY = 11;
	m_turning_animation_sprites[23]->spriteWidth = 905 - 874;
	m_turning_animation_sprites[23]->spriteHeight = 47 - 11;

}
