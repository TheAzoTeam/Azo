#include "player.hpp"

using namespace Azo;

Player::Player(){}

Player::Player(std::string name, std::pair<double, double> current_position){
	DEBUG("Player::Player method.");

	mName = name;
	mCurrentPosition = current_position;
	CreateComponents();
}

void Player::Shutdown(){

	if(m_anim_controller != nullptr){
		DEBUG("Shutting down m_anim_controller");
		m_anim_controller->Shutdown();
		delete(m_anim_controller);
		m_anim_controller = nullptr;
	}

	for(auto each_sprite : m_walking_animation_sprites){
		if(each_sprite != nullptr){
			each_sprite = nullptr;
		}
	}

	for(auto each_sprite : m_jumping_animation_sprites){
		if(each_sprite != nullptr){
			each_sprite = nullptr;
		}
	}

	for(auto each_sprite : m_sliding_animation_sprites){
		if(each_sprite != nullptr){
			each_sprite = nullptr;
		}
	}

	for(auto each_sprite : m_dying_animation_sprites){
		if(each_sprite != nullptr){
			each_sprite = nullptr;
		}
	}


	if(m_walking != nullptr){
		delete(m_walking);
		m_walking = nullptr;
	}

	if(m_jumping != nullptr){
		delete(m_jumping);
		m_jumping = nullptr;
	}

	if(m_sliding != nullptr){
		delete(m_sliding);
		m_sliding = nullptr;
	}

	if(m_dying != nullptr){
		delete(m_dying);
		m_dying = nullptr;
	}

	if(m_losing != nullptr){
		delete(m_losing);
		m_losing = nullptr;
	}

	if(m_player_code != nullptr){
		m_player_code->Shutdown();
		delete(m_player_code);
		m_player_code = nullptr;
	}
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

	GenSlidingAnimation();
	m_sliding = new engine::Animation(*this, "sprites/CowboyDesce.png", 800.0f, m_sliding_animation_sprites, 0, 20, false, 1);
	m_sliding->DisableComponent();
	m_anim_controller->AddAnimation("sliding", *m_sliding);

	GenDyingAnimation();
	m_dying = new engine::Animation(*this, "sprites/CowboyTonto.png", 2000.0f, m_dying_animation_sprites, 0, 35, false, 1);
	m_dying->DisableComponent();
	m_anim_controller->AddAnimation("dying", *m_dying);

	GenLosingAnimation();
	m_losing = new engine::Animation(*this, "sprites/CowBoyDerrota.png", 10000.0f, m_losing_animation_sprites, 0, 6, false, 1);
	m_losing->DisableComponent();
	m_anim_controller->AddAnimation("losing", *m_losing);

	GenVictoryAnimation();
	m_victory = new engine::Animation(*this, "sprites/victory.png", 10.0f, m_victory_animation_sprites, 0, 0, false, 1);
	m_victory->DisableComponent();
	m_anim_controller->AddAnimation("victory", *m_victory);

	DEBUG("Adding animation controller to Player.");
	this->addComponent(*m_anim_controller);

	m_lost = new engine::AudioComponent(*this, "audios/derrota.ogg", false, false);
	m_victory_song = new engine::AudioComponent(*this, "audios/victory.ogg", false, false);
	m_audio_controller = new engine::AudioController();
	m_audio_controller->AddAudio("lost", *m_lost);
	m_audio_controller->AddAudio("victory", *m_victory_song);

	this->addComponent(*m_audio_controller);

	DEBUG("Creating Player Code.");
	m_player_code = new PlayerCode(this);
	this->addComponent(*m_player_code);
}

void Player::GenVictoryAnimation(){
	m_victory_animation_sprites.push_back(new engine::Sprite());

	m_victory_animation_sprites[0]->sprite_x = 0;
	m_victory_animation_sprites[0]->sprite_y = 0;
	m_victory_animation_sprites[0]->sprite_width = 180;
	m_victory_animation_sprites[0]->sprite_height = 140;
}


void Player::GenLosingAnimation(){
	for(int i = 0; i < 7; i++){
		m_losing_animation_sprites.push_back(new engine::Sprite());
	}

	m_losing_animation_sprites[0]->sprite_x = 1;
	m_losing_animation_sprites[0]->sprite_y = 1;
	m_losing_animation_sprites[0]->sprite_width = 70 - 1;
	m_losing_animation_sprites[0]->sprite_height = 111 - 1;

	m_losing_animation_sprites[1]->sprite_x = 72;
	m_losing_animation_sprites[1]->sprite_y = 1;
	m_losing_animation_sprites[1]->sprite_width = 141 - 72;
	m_losing_animation_sprites[1]->sprite_height = 111 - 1;

	m_losing_animation_sprites[2]->sprite_x = 1;
	m_losing_animation_sprites[2]->sprite_y = 1;
	m_losing_animation_sprites[2]->sprite_width = 70 - 1;
	m_losing_animation_sprites[2]->sprite_height = 111 - 1;

	m_losing_animation_sprites[3]->sprite_x = 72;
	m_losing_animation_sprites[3]->sprite_y = 1;
	m_losing_animation_sprites[3]->sprite_width = 141 - 72;
	m_losing_animation_sprites[3]->sprite_height = 111 - 1;

	m_losing_animation_sprites[4]->sprite_x = 1;
	m_losing_animation_sprites[4]->sprite_y = 1;
	m_losing_animation_sprites[4]->sprite_width = 70 - 1;
	m_losing_animation_sprites[4]->sprite_height = 111 - 1;

	m_losing_animation_sprites[5]->sprite_x = 72;
	m_losing_animation_sprites[5]->sprite_y = 1;
	m_losing_animation_sprites[5]->sprite_width = 141 - 72;
	m_losing_animation_sprites[5]->sprite_height = 111 - 1;

	m_losing_animation_sprites[6]->sprite_x = 147;
	m_losing_animation_sprites[6]->sprite_y = 4;
	m_losing_animation_sprites[6]->sprite_width = 209 - 147;
	m_losing_animation_sprites[6]->sprite_height = 111 - 4;
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

void Player::GenSlidingAnimation(){
	for(int i = 0; i < 21; i++){
		m_sliding_animation_sprites.push_back(new engine::Sprite());
	}

	m_sliding_animation_sprites[0]->sprite_x = 1;
	m_sliding_animation_sprites[0]->sprite_y = 59;
	m_sliding_animation_sprites[0]->sprite_width = 107 - 1;
	m_sliding_animation_sprites[0]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[1]->sprite_x = 109;
	m_sliding_animation_sprites[1]->sprite_y = 59;
	m_sliding_animation_sprites[1]->sprite_width = 215 - 109;
	m_sliding_animation_sprites[1]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[2]->sprite_x = 217;
	m_sliding_animation_sprites[2]->sprite_y = 59;
	m_sliding_animation_sprites[2]->sprite_width = 323 - 217;
	m_sliding_animation_sprites[2]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[3]->sprite_x = 325;
	m_sliding_animation_sprites[3]->sprite_y = 59;
	m_sliding_animation_sprites[3]->sprite_width = 431 - 325;
	m_sliding_animation_sprites[3]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[4]->sprite_x = 433;
	m_sliding_animation_sprites[4]->sprite_y = 59;
	m_sliding_animation_sprites[4]->sprite_width = 539 - 433;
	m_sliding_animation_sprites[4]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[5]->sprite_x = 541;
	m_sliding_animation_sprites[5]->sprite_y = 59;
	m_sliding_animation_sprites[5]->sprite_width = 647 - 541;
	m_sliding_animation_sprites[5]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[6]->sprite_x = 649;
	m_sliding_animation_sprites[6]->sprite_y = 59;
	m_sliding_animation_sprites[6]->sprite_width = 755 - 649;
	m_sliding_animation_sprites[6]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[7]->sprite_x = 757;
	m_sliding_animation_sprites[7]->sprite_y = 59;
	m_sliding_animation_sprites[7]->sprite_width = 863 - 757;
	m_sliding_animation_sprites[7]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[8]->sprite_x = 865;
	m_sliding_animation_sprites[8]->sprite_y = 59;
	m_sliding_animation_sprites[8]->sprite_width = 971 - 865;
	m_sliding_animation_sprites[8]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[9]->sprite_x = 979;
	m_sliding_animation_sprites[9]->sprite_y = 59;
	m_sliding_animation_sprites[9]->sprite_width = 1079 - 979;
	m_sliding_animation_sprites[9]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[10]->sprite_x = 1087;
	m_sliding_animation_sprites[10]->sprite_y = 59;
	m_sliding_animation_sprites[10]->sprite_width = 1187 - 1087;
	m_sliding_animation_sprites[10]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[11]->sprite_x = 1195;
	m_sliding_animation_sprites[11]->sprite_y = 59;
	m_sliding_animation_sprites[11]->sprite_width = 1295 - 1195;
	m_sliding_animation_sprites[11]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[12]->sprite_x = 1303;
	m_sliding_animation_sprites[12]->sprite_y = 59;
	m_sliding_animation_sprites[12]->sprite_width = 1403 - 1303;
	m_sliding_animation_sprites[12]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[13]->sprite_x = 1411;
	m_sliding_animation_sprites[13]->sprite_y = 59;
	m_sliding_animation_sprites[13]->sprite_width = 1511 - 1411;
	m_sliding_animation_sprites[13]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[14]->sprite_x = 1519;
	m_sliding_animation_sprites[14]->sprite_y = 59;
	m_sliding_animation_sprites[14]->sprite_width = 1619 - 1519;
	m_sliding_animation_sprites[14]->sprite_height = 139 - 59;

	m_sliding_animation_sprites[15]->sprite_x = 1640;
	m_sliding_animation_sprites[15]->sprite_y = 40;
	m_sliding_animation_sprites[15]->sprite_width = 1727 - 1640;
	m_sliding_animation_sprites[15]->sprite_height = 139 - 40;

	m_sliding_animation_sprites[16]->sprite_x = 1748;
	m_sliding_animation_sprites[16]->sprite_y = 40;
	m_sliding_animation_sprites[16]->sprite_width = 1853 - 1748;
	m_sliding_animation_sprites[16]->sprite_height = 139 - 40;

	m_sliding_animation_sprites[17]->sprite_x = 1856;
	m_sliding_animation_sprites[17]->sprite_y = 40;
	m_sliding_animation_sprites[17]->sprite_width = 1943 - 1856;
	m_sliding_animation_sprites[17]->sprite_height = 139 - 40;

	m_sliding_animation_sprites[18]->sprite_x = 1964;
	m_sliding_animation_sprites[18]->sprite_y = 40;
	m_sliding_animation_sprites[18]->sprite_width = 2051 - 1964;
	m_sliding_animation_sprites[18]->sprite_height = 139 - 40;

	m_sliding_animation_sprites[19]->sprite_x = 2072;
	m_sliding_animation_sprites[19]->sprite_y = 40;
	m_sliding_animation_sprites[19]->sprite_width = 2159 - 2072;
	m_sliding_animation_sprites[19]->sprite_height = 139 - 40;

	m_sliding_animation_sprites[20]->sprite_x = 2180;
	m_sliding_animation_sprites[20]->sprite_y = 40;
	m_sliding_animation_sprites[20]->sprite_width = 2267 - 2180;
	m_sliding_animation_sprites[20]->sprite_height = 139 - 40;
}

void Player::GenDyingAnimation(){
	for(int i = 0; i < 36; i++){
		m_dying_animation_sprites.push_back(new engine::Sprite());
	}

	m_dying_animation_sprites[0]->sprite_x = 4;
	m_dying_animation_sprites[0]->sprite_y = 47;
	m_dying_animation_sprites[0]->sprite_width = 73 - 4;
	m_dying_animation_sprites[0]->sprite_height = 138 - 47;

	m_dying_animation_sprites[1]->sprite_x = 112;
	m_dying_animation_sprites[1]->sprite_y = 47;
	m_dying_animation_sprites[1]->sprite_width = 181 - 112;
	m_dying_animation_sprites[1]->sprite_height = 138 - 47;

	m_dying_animation_sprites[2]->sprite_x = 220;
	m_dying_animation_sprites[2]->sprite_y = 47;
	m_dying_animation_sprites[2]->sprite_width = 289 - 220;
	m_dying_animation_sprites[2]->sprite_height = 138 - 47;

	m_dying_animation_sprites[3]->sprite_x = 328;
	m_dying_animation_sprites[3]->sprite_y = 47;
	m_dying_animation_sprites[3]->sprite_width = 397 - 328;
	m_dying_animation_sprites[3]->sprite_height = 138 - 47;

	m_dying_animation_sprites[4]->sprite_x = 436;
	m_dying_animation_sprites[4]->sprite_y = 47;
	m_dying_animation_sprites[4]->sprite_width = 505 - 436;
	m_dying_animation_sprites[4]->sprite_height = 138 - 47;

	m_dying_animation_sprites[5]->sprite_x = 544;
	m_dying_animation_sprites[5]->sprite_y = 47;
	m_dying_animation_sprites[5]->sprite_width = 613 - 544;
	m_dying_animation_sprites[5]->sprite_height = 138 - 47;

	m_dying_animation_sprites[6]->sprite_x = 652;
	m_dying_animation_sprites[6]->sprite_y = 47;
	m_dying_animation_sprites[6]->sprite_width = 721 - 652;
	m_dying_animation_sprites[6]->sprite_height = 138 - 47;

	m_dying_animation_sprites[7]->sprite_x = 760;
	m_dying_animation_sprites[7]->sprite_y = 47;
	m_dying_animation_sprites[7]->sprite_width = 829 - 760;
	m_dying_animation_sprites[7]->sprite_height = 138 - 47;

	m_dying_animation_sprites[8]->sprite_x = 868;
	m_dying_animation_sprites[8]->sprite_y = 47;
	m_dying_animation_sprites[8]->sprite_width = 937 - 868;
	m_dying_animation_sprites[8]->sprite_height = 138 - 47;

	m_dying_animation_sprites[9]->sprite_x = 976;
	m_dying_animation_sprites[9]->sprite_y = 47;
	m_dying_animation_sprites[9]->sprite_width = 1045 - 976;
	m_dying_animation_sprites[9]->sprite_height = 138 - 47;

	m_dying_animation_sprites[10]->sprite_x = 1084;
	m_dying_animation_sprites[10]->sprite_y = 47;
	m_dying_animation_sprites[10]->sprite_width = 1153 - 1084;
	m_dying_animation_sprites[10]->sprite_height = 138 - 47;

	m_dying_animation_sprites[11]->sprite_x = 1192;
	m_dying_animation_sprites[11]->sprite_y = 47;
	m_dying_animation_sprites[11]->sprite_width = 1261 - 1192;
	m_dying_animation_sprites[11]->sprite_height = 138 - 47;

	m_dying_animation_sprites[12]->sprite_x = 1300;
	m_dying_animation_sprites[12]->sprite_y = 47;
	m_dying_animation_sprites[12]->sprite_width = 1369 - 1300;
	m_dying_animation_sprites[12]->sprite_height = 138 - 47;

	m_dying_animation_sprites[13]->sprite_x = 1408;
	m_dying_animation_sprites[13]->sprite_y = 47;
	m_dying_animation_sprites[13]->sprite_width = 1477 - 1408;
	m_dying_animation_sprites[13]->sprite_height = 138 - 47;

	m_dying_animation_sprites[14]->sprite_x = 1516;
	m_dying_animation_sprites[14]->sprite_y = 47;
	m_dying_animation_sprites[14]->sprite_width = 1585 - 1516;
	m_dying_animation_sprites[14]->sprite_height = 138 - 47;

	m_dying_animation_sprites[15]->sprite_x = 1624;
	m_dying_animation_sprites[15]->sprite_y = 47;
	m_dying_animation_sprites[15]->sprite_width = 1693 - 1624;
	m_dying_animation_sprites[15]->sprite_height = 138 - 47;

	m_dying_animation_sprites[16]->sprite_x = 1732;
	m_dying_animation_sprites[16]->sprite_y = 47;
	m_dying_animation_sprites[16]->sprite_width = 1801 - 1732;
	m_dying_animation_sprites[16]->sprite_height = 138 - 47;

	m_dying_animation_sprites[17]->sprite_x = 1840;
	m_dying_animation_sprites[17]->sprite_y = 47;
	m_dying_animation_sprites[17]->sprite_width = 1909 - 1840;
	m_dying_animation_sprites[17]->sprite_height = 138 - 47;

	m_dying_animation_sprites[18]->sprite_x = 1948;
	m_dying_animation_sprites[18]->sprite_y = 47;
	m_dying_animation_sprites[18]->sprite_width = 2017 - 1948;
	m_dying_animation_sprites[18]->sprite_height = 139 - 47;

	m_dying_animation_sprites[19]->sprite_x = 2056;
	m_dying_animation_sprites[19]->sprite_y = 47;
	m_dying_animation_sprites[19]->sprite_width = 2152 - 2056;
	m_dying_animation_sprites[19]->sprite_height = 139 - 47;

	m_dying_animation_sprites[20]->sprite_x = 2164;
	m_dying_animation_sprites[20]->sprite_y = 47;
	m_dying_animation_sprites[20]->sprite_width = 2233 - 2164;
	m_dying_animation_sprites[20]->sprite_height = 139 - 47;

	m_dying_animation_sprites[21]->sprite_x = 2272;
	m_dying_animation_sprites[21]->sprite_y = 47;
	m_dying_animation_sprites[21]->sprite_width = 2341 - 2272;
	m_dying_animation_sprites[21]->sprite_height = 139 - 47;

	m_dying_animation_sprites[22]->sprite_x = 2380;
	m_dying_animation_sprites[22]->sprite_y = 47;
	m_dying_animation_sprites[22]->sprite_width = 2449 - 2380;
	m_dying_animation_sprites[22]->sprite_height = 139 - 47;

	m_dying_animation_sprites[23]->sprite_x = 2488;
	m_dying_animation_sprites[23]->sprite_y = 47;
	m_dying_animation_sprites[23]->sprite_width = 2557 - 2488;
	m_dying_animation_sprites[23]->sprite_height = 139 - 47;

	m_dying_animation_sprites[24]->sprite_x = 2596;
	m_dying_animation_sprites[24]->sprite_y = 47;
	m_dying_animation_sprites[24]->sprite_width = 2665 - 2596;
	m_dying_animation_sprites[24]->sprite_height = 139 - 47;

	m_dying_animation_sprites[25]->sprite_x = 2704;
	m_dying_animation_sprites[25]->sprite_y = 47;
	m_dying_animation_sprites[25]->sprite_width = 2773 - 2704;
	m_dying_animation_sprites[25]->sprite_height = 139 - 47;

	m_dying_animation_sprites[26]->sprite_x = 2812;
	m_dying_animation_sprites[26]->sprite_y = 47;
	m_dying_animation_sprites[26]->sprite_width = 2881 - 2812;
	m_dying_animation_sprites[26]->sprite_height = 139 - 47;

	m_dying_animation_sprites[27]->sprite_x = 2920;
	m_dying_animation_sprites[27]->sprite_y = 47;
	m_dying_animation_sprites[27]->sprite_width = 2989 - 2920;
	m_dying_animation_sprites[27]->sprite_height = 139 - 47;

	m_dying_animation_sprites[28]->sprite_x = 3028;
	m_dying_animation_sprites[28]->sprite_y = 47;
	m_dying_animation_sprites[28]->sprite_width = 3097 - 3028;
	m_dying_animation_sprites[28]->sprite_height = 139 - 47;

	m_dying_animation_sprites[29]->sprite_x = 3136;
	m_dying_animation_sprites[29]->sprite_y = 47;
	m_dying_animation_sprites[29]->sprite_width = 3205 - 3136;
	m_dying_animation_sprites[29]->sprite_height = 139 - 47;

	m_dying_animation_sprites[30]->sprite_x = 3244;
	m_dying_animation_sprites[30]->sprite_y = 47;
	m_dying_animation_sprites[30]->sprite_width = 3313 - 3244;
	m_dying_animation_sprites[30]->sprite_height = 139 - 47;

	m_dying_animation_sprites[31]->sprite_x = 3352;
	m_dying_animation_sprites[31]->sprite_y = 47;
	m_dying_animation_sprites[31]->sprite_width = 3421 - 3352;
	m_dying_animation_sprites[31]->sprite_height = 139 - 47;

	m_dying_animation_sprites[32]->sprite_x = 3460;
	m_dying_animation_sprites[32]->sprite_y = 47;
	m_dying_animation_sprites[32]->sprite_width = 3529 - 3460;
	m_dying_animation_sprites[32]->sprite_height = 139 - 47;

	m_dying_animation_sprites[33]->sprite_x = 3568;
	m_dying_animation_sprites[33]->sprite_y = 47;
	m_dying_animation_sprites[33]->sprite_width = 3637 - 3568;
	m_dying_animation_sprites[33]->sprite_height = 139 - 47;

	m_dying_animation_sprites[34]->sprite_x = 3676;
	m_dying_animation_sprites[34]->sprite_y = 47;
	m_dying_animation_sprites[34]->sprite_width = 3745 - 3676;
	m_dying_animation_sprites[34]->sprite_height = 139 - 47;

	m_dying_animation_sprites[35]->sprite_x = 3784;
	m_dying_animation_sprites[35]->sprite_y = 47;
	m_dying_animation_sprites[35]->sprite_width = 3853 - 3784;
	m_dying_animation_sprites[35]->sprite_height = 139 - 47;
}