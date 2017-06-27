#include "player.hpp"

using namespace Azo;

Player::Player(){}

Player::Player(std::string name, std::pair<double, double> current_position){
	DEBUG("Player::Player method.");

	m_name = name;
	m_current_position = current_position;
	CreateComponents();
}

void Player::CreateComponents(){
	DEBUG("Creating Player Components.");
	GenWalkingAnimation();
	m_walking = new engine::Animation(*this, "sprites/CowboyRun.png", 1000.0f, m_walking_animation_sprites, 0, 22, true, 1);

	m_anim_controller = new engine::AnimationController();

	DEBUG("Adding walking animation to animation controller.");
	m_anim_controller->AddAnimation("walking", *m_walking);

	GenJumpingAnimation();
	m_jumping = new engine::Animation(*this, "sprites/CowboyJump.png", 800.0f, m_jumping_animation_sprites, 0, 7, false, 1);
	m_jumping->DisableComponent();
	DEBUG("Adding jumping animation to animation controller");
	m_anim_controller->AddAnimation("jumping", *m_jumping);

	DEBUG("Adding animation controller to Player.");
	this->AddComponent(*m_anim_controller);

	DEBUG("Creating Player Code.");
	m_player_code = new PlayerCode(this);
	this->AddComponent(*m_player_code);
}

void Player::GenWalkingAnimation(){
	DEBUG("Generating player walking animation.");
	for(int i = 0; i < 23; i++){
		m_walking_animation_sprites.push_back(new engine::Sprite());
	}

	m_walking_animation_sprites[0]->sprite_x = 2;
	m_walking_animation_sprites[0]->sprite_y = 34;
	m_walking_animation_sprites[0]->sprite_width = 67 - 2;
	m_walking_animation_sprites[0]->sprite_height = 139 - 34;

	m_walking_animation_sprites[1]->sprite_x = 71;
	m_walking_animation_sprites[1]->sprite_y = 34;
	m_walking_animation_sprites[1]->sprite_width = 136 - 71;
	m_walking_animation_sprites[1]->sprite_height = 139 - 34;

	m_walking_animation_sprites[2]->sprite_x = 137;
	m_walking_animation_sprites[2]->sprite_y = 34;
	m_walking_animation_sprites[2]->sprite_width = 202 - 137;
	m_walking_animation_sprites[2]->sprite_height = 139 - 34;

	m_walking_animation_sprites[3]->sprite_x = 203;
	m_walking_animation_sprites[3]->sprite_y = 20;
	m_walking_animation_sprites[3]->sprite_width = 273 - 203;
	m_walking_animation_sprites[3]->sprite_height = 139 - 20;

	m_walking_animation_sprites[4]->sprite_x = 274;
	m_walking_animation_sprites[4]->sprite_y = 20;
	m_walking_animation_sprites[4]->sprite_width = 344 - 274;
	m_walking_animation_sprites[4]->sprite_height = 139 - 20;

	m_walking_animation_sprites[5]->sprite_x = 345;
	m_walking_animation_sprites[5]->sprite_y = 20;
	m_walking_animation_sprites[5]->sprite_width = 415 - 345;
	m_walking_animation_sprites[5]->sprite_height = 139 - 20;

	m_walking_animation_sprites[6]->sprite_x = 416;
	m_walking_animation_sprites[6]->sprite_y = 26;
	m_walking_animation_sprites[6]->sprite_width = 501 - 416;
	m_walking_animation_sprites[6]->sprite_height = 139 - 26;

	m_walking_animation_sprites[7]->sprite_x = 502;
	m_walking_animation_sprites[7]->sprite_y = 26;
	m_walking_animation_sprites[7]->sprite_width = 585 - 502;
	m_walking_animation_sprites[7]->sprite_height = 139 - 26;

	m_walking_animation_sprites[8]->sprite_x = 587;
	m_walking_animation_sprites[8]->sprite_y = 26;
	m_walking_animation_sprites[8]->sprite_width = 672 - 587;
	m_walking_animation_sprites[8]->sprite_height = 139 - 26;

	m_walking_animation_sprites[9]->sprite_x = 673;
	m_walking_animation_sprites[9]->sprite_y = 26;
	m_walking_animation_sprites[9]->sprite_width = 744 - 673;
	m_walking_animation_sprites[9]->sprite_height = 139 - 26;

	m_walking_animation_sprites[10]->sprite_x = 745;
	m_walking_animation_sprites[10]->sprite_y = 26;
	m_walking_animation_sprites[10]->sprite_width = 816 - 745;
	m_walking_animation_sprites[10]->sprite_height = 139 - 26;

	m_walking_animation_sprites[11]->sprite_x = 889;
	m_walking_animation_sprites[11]->sprite_y = 26;
	m_walking_animation_sprites[11]->sprite_width = 960 - 889;
	m_walking_animation_sprites[11]->sprite_height = 139 - 26;

	m_walking_animation_sprites[12]->sprite_x = 961;
	m_walking_animation_sprites[12]->sprite_y = 34;
	m_walking_animation_sprites[12]->sprite_width = 1029 - 961;
	m_walking_animation_sprites[12]->sprite_height = 139 - 34;

	m_walking_animation_sprites[13]->sprite_x = 1031;
	m_walking_animation_sprites[13]->sprite_y = 34;
	m_walking_animation_sprites[13]->sprite_width = 1099 - 1031;
	m_walking_animation_sprites[13]->sprite_height = 139 - 34;

	m_walking_animation_sprites[14]->sprite_x = 1100;
	m_walking_animation_sprites[14]->sprite_y = 20;
	m_walking_animation_sprites[14]->sprite_width = 1165 - 1100;
	m_walking_animation_sprites[14]->sprite_height = 139 - 20;

	m_walking_animation_sprites[15]->sprite_x = 1166;
	m_walking_animation_sprites[15]->sprite_y = 20;
	m_walking_animation_sprites[15]->sprite_width = 1231 - 1166;
	m_walking_animation_sprites[15]->sprite_height = 139 - 20;

	m_walking_animation_sprites[16]->sprite_x = 1232;
	m_walking_animation_sprites[16]->sprite_y = 20;
	m_walking_animation_sprites[16]->sprite_width = 1296 - 1232;
	m_walking_animation_sprites[16]->sprite_height = 139 - 20;

	m_walking_animation_sprites[17]->sprite_x = 1297;
	m_walking_animation_sprites[17]->sprite_y = 26;
	m_walking_animation_sprites[17]->sprite_width = 1382 - 1297;
	m_walking_animation_sprites[17]->sprite_height = 139 - 26;

	m_walking_animation_sprites[18]->sprite_x = 1383;
	m_walking_animation_sprites[18]->sprite_y = 26;
	m_walking_animation_sprites[18]->sprite_width = 1468 - 1383;
	m_walking_animation_sprites[18]->sprite_height = 139 - 26;

	m_walking_animation_sprites[19]->sprite_x = 1469;
	m_walking_animation_sprites[19]->sprite_y = 26;
	m_walking_animation_sprites[19]->sprite_width = 1554 - 1469;
	m_walking_animation_sprites[19]->sprite_height = 139 - 26;

	m_walking_animation_sprites[20]->sprite_x = 1555;
	m_walking_animation_sprites[20]->sprite_y = 29;
	m_walking_animation_sprites[20]->sprite_width = 1629 - 1555;
	m_walking_animation_sprites[20]->sprite_height = 139 - 29;

	m_walking_animation_sprites[21]->sprite_x = 1631;
	m_walking_animation_sprites[21]->sprite_y = 29;
	m_walking_animation_sprites[21]->sprite_width = 1707 - 1631;
	m_walking_animation_sprites[21]->sprite_height = 139 - 29;

	m_walking_animation_sprites[22]->sprite_x = 1709;
	m_walking_animation_sprites[22]->sprite_y = 29;
	m_walking_animation_sprites[22]->sprite_width = 1784 - 1709;
	m_walking_animation_sprites[22]->sprite_height = 139 - 29;
}

void Player::GenJumpingAnimation(){
	DEBUG("Generating Player Jumping Animation.");

	for(int i = 0; i < 8; i++){
		m_jumping_animation_sprites.push_back(new engine::Sprite());
	}

	m_jumping_animation_sprites[0]->sprite_x = 20;
	m_jumping_animation_sprites[0]->sprite_y = 22;
	m_jumping_animation_sprites[0]->sprite_width = 94 - 20;
	m_jumping_animation_sprites[0]->sprite_height = 127 - 22;

	m_jumping_animation_sprites[1]->sprite_x = 14;
	m_jumping_animation_sprites[1]->sprite_y = 168;
	m_jumping_animation_sprites[1]->sprite_width = 97 - 24;
	m_jumping_animation_sprites[1]->sprite_height = 267 - 168;

	m_jumping_animation_sprites[2]->sprite_x = 8;
	m_jumping_animation_sprites[2]->sprite_y = 282;
	m_jumping_animation_sprites[2]->sprite_width = 103 - 8;
	m_jumping_animation_sprites[2]->sprite_height = 398 - 282;

	m_jumping_animation_sprites[3]->sprite_x = 8;
	m_jumping_animation_sprites[3]->sprite_y = 422;
	m_jumping_animation_sprites[3]->sprite_width = 103 - 8;
	m_jumping_animation_sprites[3]->sprite_height = 538 - 422;

	m_jumping_animation_sprites[4]->sprite_x = 16;
	m_jumping_animation_sprites[4]->sprite_y = 562;
	m_jumping_animation_sprites[4]->sprite_width = 97 - 16;
	m_jumping_animation_sprites[4]->sprite_height = 678 - 562;

	m_jumping_animation_sprites[5]->sprite_x = 16;
	m_jumping_animation_sprites[5]->sprite_y = 702;
	m_jumping_animation_sprites[5]->sprite_width = 97 - 16;
	m_jumping_animation_sprites[5]->sprite_height = 818 - 702;

	m_jumping_animation_sprites[6]->sprite_x = 16;
	m_jumping_animation_sprites[6]->sprite_y = 842;
	m_jumping_animation_sprites[6]->sprite_width = 99 - 16;
	m_jumping_animation_sprites[6]->sprite_height = 958 - 842;

	m_jumping_animation_sprites[7]->sprite_x = 14;
	m_jumping_animation_sprites[7]->sprite_y = 997;
	m_jumping_animation_sprites[7]->sprite_width = 83 - 20;
	m_jumping_animation_sprites[7]->sprite_height = 1107 - 997;
}
