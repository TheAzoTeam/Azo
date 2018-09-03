#include "player.hpp"

using namespace Azo;

Player::Player(){}

Player::Player(std::string name, std::pair<double, double> current_position){
	DEBUG("Player::Player method.");

	m_name = name;
	m_current_position = current_position;
	CreateComponents();
}

void Player::shutdown(){

	if(m_anim_controller != nullptr){
		DEBUG("Shutting down m_anim_controller");
		m_anim_controller->shutdown();
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
		m_player_code->shutdown();
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
	m_anim_controller->addAnimation("walking", *m_walking);

	GenJumpingAnimation();
	m_jumping = new engine::Animation(*this, "sprites/CowboyJump.png", 800.0f, m_jumping_animation_sprites, 0, 7, false, 1);
	m_jumping->disableComponent();
	DEBUG("Adding jumping animation to animation controller");
	m_anim_controller->addAnimation("jumping", *m_jumping);

	GenSlidingAnimation();
	m_sliding = new engine::Animation(*this, "sprites/CowboyDesce.png", 800.0f, m_sliding_animation_sprites, 0, 20, false, 1);
	m_sliding->disableComponent();
	m_anim_controller->addAnimation("sliding", *m_sliding);

	GenDyingAnimation();
	m_dying = new engine::Animation(*this, "sprites/CowboyTonto.png", 2000.0f, m_dying_animation_sprites, 0, 35, false, 1);
	m_dying->disableComponent();
	m_anim_controller->addAnimation("dying", *m_dying);

	GenLosingAnimation();
	m_losing = new engine::Animation(*this, "sprites/CowBoyDerrota.png", 10000.0f, m_losing_animation_sprites, 0, 6, false, 1);
	m_losing->disableComponent();
	m_anim_controller->addAnimation("losing", *m_losing);

	GenVictoryAnimation();
	m_victory = new engine::Animation(*this, "sprites/victory.png", 10.0f, m_victory_animation_sprites, 0, 0, false, 1);
	m_victory->disableComponent();
	m_anim_controller->addAnimation("victory", *m_victory);

	DEBUG("Adding animation controller to Player.");
	this->AddComponent(*m_anim_controller);

	m_lost = new engine::AudioComponent(*this, "audios/derrota.ogg", false, false);
	m_victory_song = new engine::AudioComponent(*this, "audios/victory.ogg", false, false);
	m_audio_controller = new engine::AudioController();
	m_audio_controller->AddAudio("lost", *m_lost);
	m_audio_controller->AddAudio("victory", *m_victory_song);

	this->AddComponent(*m_audio_controller);

	DEBUG("Creating Player Code.");
	m_player_code = new PlayerCode(this);
	this->AddComponent(*m_player_code);
}

void Player::GenVictoryAnimation(){
	m_victory_animation_sprites.push_back(new engine::Sprite());

	m_victory_animation_sprites[0]->spriteX = 0;
	m_victory_animation_sprites[0]->spriteY = 0;
	m_victory_animation_sprites[0]->spriteWidth = 180;
	m_victory_animation_sprites[0]->spriteHeight = 140;
}


void Player::GenLosingAnimation(){
	for(int i = 0; i < 7; i++){
		m_losing_animation_sprites.push_back(new engine::Sprite());
	}

	m_losing_animation_sprites[0]->spriteX = 1;
	m_losing_animation_sprites[0]->spriteY = 1;
	m_losing_animation_sprites[0]->spriteWidth = 70 - 1;
	m_losing_animation_sprites[0]->spriteHeight = 111 - 1;

	m_losing_animation_sprites[1]->spriteX = 72;
	m_losing_animation_sprites[1]->spriteY = 1;
	m_losing_animation_sprites[1]->spriteWidth = 141 - 72;
	m_losing_animation_sprites[1]->spriteHeight = 111 - 1;

	m_losing_animation_sprites[2]->spriteX = 1;
	m_losing_animation_sprites[2]->spriteY = 1;
	m_losing_animation_sprites[2]->spriteWidth = 70 - 1;
	m_losing_animation_sprites[2]->spriteHeight = 111 - 1;

	m_losing_animation_sprites[3]->spriteX = 72;
	m_losing_animation_sprites[3]->spriteY = 1;
	m_losing_animation_sprites[3]->spriteWidth = 141 - 72;
	m_losing_animation_sprites[3]->spriteHeight = 111 - 1;

	m_losing_animation_sprites[4]->spriteX = 1;
	m_losing_animation_sprites[4]->spriteY = 1;
	m_losing_animation_sprites[4]->spriteWidth = 70 - 1;
	m_losing_animation_sprites[4]->spriteHeight = 111 - 1;

	m_losing_animation_sprites[5]->spriteX = 72;
	m_losing_animation_sprites[5]->spriteY = 1;
	m_losing_animation_sprites[5]->spriteWidth = 141 - 72;
	m_losing_animation_sprites[5]->spriteHeight = 111 - 1;

	m_losing_animation_sprites[6]->spriteX = 147;
	m_losing_animation_sprites[6]->spriteY = 4;
	m_losing_animation_sprites[6]->spriteWidth = 209 - 147;
	m_losing_animation_sprites[6]->spriteHeight = 111 - 4;
}


void Player::GenWalkingAnimation(){
	DEBUG("Generating player walking animation.");
	for(int i = 0; i < 23; i++){
		m_walking_animation_sprites.push_back(new engine::Sprite());
	}

	m_walking_animation_sprites[0]->spriteX = 2;
	m_walking_animation_sprites[0]->spriteY = 34;
	m_walking_animation_sprites[0]->spriteWidth = 67 - 2;
	m_walking_animation_sprites[0]->spriteHeight = 139 - 34;

	m_walking_animation_sprites[1]->spriteX = 71;
	m_walking_animation_sprites[1]->spriteY = 34;
	m_walking_animation_sprites[1]->spriteWidth = 136 - 71;
	m_walking_animation_sprites[1]->spriteHeight = 139 - 34;

	m_walking_animation_sprites[2]->spriteX = 137;
	m_walking_animation_sprites[2]->spriteY = 34;
	m_walking_animation_sprites[2]->spriteWidth = 202 - 137;
	m_walking_animation_sprites[2]->spriteHeight = 139 - 34;

	m_walking_animation_sprites[3]->spriteX = 203;
	m_walking_animation_sprites[3]->spriteY = 20;
	m_walking_animation_sprites[3]->spriteWidth = 273 - 203;
	m_walking_animation_sprites[3]->spriteHeight = 139 - 20;

	m_walking_animation_sprites[4]->spriteX = 274;
	m_walking_animation_sprites[4]->spriteY = 20;
	m_walking_animation_sprites[4]->spriteWidth = 344 - 274;
	m_walking_animation_sprites[4]->spriteHeight = 139 - 20;

	m_walking_animation_sprites[5]->spriteX = 345;
	m_walking_animation_sprites[5]->spriteY = 20;
	m_walking_animation_sprites[5]->spriteWidth = 415 - 345;
	m_walking_animation_sprites[5]->spriteHeight = 139 - 20;

	m_walking_animation_sprites[6]->spriteX = 416;
	m_walking_animation_sprites[6]->spriteY = 26;
	m_walking_animation_sprites[6]->spriteWidth = 501 - 416;
	m_walking_animation_sprites[6]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[7]->spriteX = 502;
	m_walking_animation_sprites[7]->spriteY = 26;
	m_walking_animation_sprites[7]->spriteWidth = 585 - 502;
	m_walking_animation_sprites[7]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[8]->spriteX = 587;
	m_walking_animation_sprites[8]->spriteY = 26;
	m_walking_animation_sprites[8]->spriteWidth = 672 - 587;
	m_walking_animation_sprites[8]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[9]->spriteX = 673;
	m_walking_animation_sprites[9]->spriteY = 26;
	m_walking_animation_sprites[9]->spriteWidth = 744 - 673;
	m_walking_animation_sprites[9]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[10]->spriteX = 745;
	m_walking_animation_sprites[10]->spriteY = 26;
	m_walking_animation_sprites[10]->spriteWidth = 816 - 745;
	m_walking_animation_sprites[10]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[11]->spriteX = 889;
	m_walking_animation_sprites[11]->spriteY = 26;
	m_walking_animation_sprites[11]->spriteWidth = 960 - 889;
	m_walking_animation_sprites[11]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[12]->spriteX = 961;
	m_walking_animation_sprites[12]->spriteY = 34;
	m_walking_animation_sprites[12]->spriteWidth = 1029 - 961;
	m_walking_animation_sprites[12]->spriteHeight = 139 - 34;

	m_walking_animation_sprites[13]->spriteX = 1031;
	m_walking_animation_sprites[13]->spriteY = 34;
	m_walking_animation_sprites[13]->spriteWidth = 1099 - 1031;
	m_walking_animation_sprites[13]->spriteHeight = 139 - 34;

	m_walking_animation_sprites[14]->spriteX = 1100;
	m_walking_animation_sprites[14]->spriteY = 20;
	m_walking_animation_sprites[14]->spriteWidth = 1165 - 1100;
	m_walking_animation_sprites[14]->spriteHeight = 139 - 20;

	m_walking_animation_sprites[15]->spriteX = 1166;
	m_walking_animation_sprites[15]->spriteY = 20;
	m_walking_animation_sprites[15]->spriteWidth = 1231 - 1166;
	m_walking_animation_sprites[15]->spriteHeight = 139 - 20;

	m_walking_animation_sprites[16]->spriteX = 1232;
	m_walking_animation_sprites[16]->spriteY = 20;
	m_walking_animation_sprites[16]->spriteWidth = 1296 - 1232;
	m_walking_animation_sprites[16]->spriteHeight = 139 - 20;

	m_walking_animation_sprites[17]->spriteX = 1297;
	m_walking_animation_sprites[17]->spriteY = 26;
	m_walking_animation_sprites[17]->spriteWidth = 1382 - 1297;
	m_walking_animation_sprites[17]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[18]->spriteX = 1383;
	m_walking_animation_sprites[18]->spriteY = 26;
	m_walking_animation_sprites[18]->spriteWidth = 1468 - 1383;
	m_walking_animation_sprites[18]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[19]->spriteX = 1469;
	m_walking_animation_sprites[19]->spriteY = 26;
	m_walking_animation_sprites[19]->spriteWidth = 1554 - 1469;
	m_walking_animation_sprites[19]->spriteHeight = 139 - 26;

	m_walking_animation_sprites[20]->spriteX = 1555;
	m_walking_animation_sprites[20]->spriteY = 29;
	m_walking_animation_sprites[20]->spriteWidth = 1629 - 1555;
	m_walking_animation_sprites[20]->spriteHeight = 139 - 29;

	m_walking_animation_sprites[21]->spriteX = 1631;
	m_walking_animation_sprites[21]->spriteY = 29;
	m_walking_animation_sprites[21]->spriteWidth = 1707 - 1631;
	m_walking_animation_sprites[21]->spriteHeight = 139 - 29;

	m_walking_animation_sprites[22]->spriteX = 1709;
	m_walking_animation_sprites[22]->spriteY = 29;
	m_walking_animation_sprites[22]->spriteWidth = 1784 - 1709;
	m_walking_animation_sprites[22]->spriteHeight = 139 - 29;
}

void Player::GenJumpingAnimation(){
	DEBUG("Generating Player Jumping Animation.");

	for(int i = 0; i < 8; i++){
		m_jumping_animation_sprites.push_back(new engine::Sprite());
	}

	m_jumping_animation_sprites[0]->spriteX = 20;
	m_jumping_animation_sprites[0]->spriteY = 22;
	m_jumping_animation_sprites[0]->spriteWidth = 94 - 20;
	m_jumping_animation_sprites[0]->spriteHeight = 127 - 22;

	m_jumping_animation_sprites[1]->spriteX = 14;
	m_jumping_animation_sprites[1]->spriteY = 168;
	m_jumping_animation_sprites[1]->spriteWidth = 97 - 24;
	m_jumping_animation_sprites[1]->spriteHeight = 267 - 168;

	m_jumping_animation_sprites[2]->spriteX = 8;
	m_jumping_animation_sprites[2]->spriteY = 282;
	m_jumping_animation_sprites[2]->spriteWidth = 103 - 8;
	m_jumping_animation_sprites[2]->spriteHeight = 398 - 282;

	m_jumping_animation_sprites[3]->spriteX = 8;
	m_jumping_animation_sprites[3]->spriteY = 422;
	m_jumping_animation_sprites[3]->spriteWidth = 103 - 8;
	m_jumping_animation_sprites[3]->spriteHeight = 538 - 422;

	m_jumping_animation_sprites[4]->spriteX = 16;
	m_jumping_animation_sprites[4]->spriteY = 562;
	m_jumping_animation_sprites[4]->spriteWidth = 97 - 16;
	m_jumping_animation_sprites[4]->spriteHeight = 678 - 562;

	m_jumping_animation_sprites[5]->spriteX = 16;
	m_jumping_animation_sprites[5]->spriteY = 702;
	m_jumping_animation_sprites[5]->spriteWidth = 97 - 16;
	m_jumping_animation_sprites[5]->spriteHeight = 818 - 702;

	m_jumping_animation_sprites[6]->spriteX = 16;
	m_jumping_animation_sprites[6]->spriteY = 842;
	m_jumping_animation_sprites[6]->spriteWidth = 99 - 16;
	m_jumping_animation_sprites[6]->spriteHeight = 958 - 842;

	m_jumping_animation_sprites[7]->spriteX = 14;
	m_jumping_animation_sprites[7]->spriteY = 997;
	m_jumping_animation_sprites[7]->spriteWidth = 83 - 20;
	m_jumping_animation_sprites[7]->spriteHeight = 1107 - 997;
}

void Player::GenSlidingAnimation(){
	for(int i = 0; i < 21; i++){
		m_sliding_animation_sprites.push_back(new engine::Sprite());
	}

	m_sliding_animation_sprites[0]->spriteX = 1;
	m_sliding_animation_sprites[0]->spriteY = 59;
	m_sliding_animation_sprites[0]->spriteWidth = 107 - 1;
	m_sliding_animation_sprites[0]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[1]->spriteX = 109;
	m_sliding_animation_sprites[1]->spriteY = 59;
	m_sliding_animation_sprites[1]->spriteWidth = 215 - 109;
	m_sliding_animation_sprites[1]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[2]->spriteX = 217;
	m_sliding_animation_sprites[2]->spriteY = 59;
	m_sliding_animation_sprites[2]->spriteWidth = 323 - 217;
	m_sliding_animation_sprites[2]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[3]->spriteX = 325;
	m_sliding_animation_sprites[3]->spriteY = 59;
	m_sliding_animation_sprites[3]->spriteWidth = 431 - 325;
	m_sliding_animation_sprites[3]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[4]->spriteX = 433;
	m_sliding_animation_sprites[4]->spriteY = 59;
	m_sliding_animation_sprites[4]->spriteWidth = 539 - 433;
	m_sliding_animation_sprites[4]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[5]->spriteX = 541;
	m_sliding_animation_sprites[5]->spriteY = 59;
	m_sliding_animation_sprites[5]->spriteWidth = 647 - 541;
	m_sliding_animation_sprites[5]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[6]->spriteX = 649;
	m_sliding_animation_sprites[6]->spriteY = 59;
	m_sliding_animation_sprites[6]->spriteWidth = 755 - 649;
	m_sliding_animation_sprites[6]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[7]->spriteX = 757;
	m_sliding_animation_sprites[7]->spriteY = 59;
	m_sliding_animation_sprites[7]->spriteWidth = 863 - 757;
	m_sliding_animation_sprites[7]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[8]->spriteX = 865;
	m_sliding_animation_sprites[8]->spriteY = 59;
	m_sliding_animation_sprites[8]->spriteWidth = 971 - 865;
	m_sliding_animation_sprites[8]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[9]->spriteX = 979;
	m_sliding_animation_sprites[9]->spriteY = 59;
	m_sliding_animation_sprites[9]->spriteWidth = 1079 - 979;
	m_sliding_animation_sprites[9]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[10]->spriteX = 1087;
	m_sliding_animation_sprites[10]->spriteY = 59;
	m_sliding_animation_sprites[10]->spriteWidth = 1187 - 1087;
	m_sliding_animation_sprites[10]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[11]->spriteX = 1195;
	m_sliding_animation_sprites[11]->spriteY = 59;
	m_sliding_animation_sprites[11]->spriteWidth = 1295 - 1195;
	m_sliding_animation_sprites[11]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[12]->spriteX = 1303;
	m_sliding_animation_sprites[12]->spriteY = 59;
	m_sliding_animation_sprites[12]->spriteWidth = 1403 - 1303;
	m_sliding_animation_sprites[12]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[13]->spriteX = 1411;
	m_sliding_animation_sprites[13]->spriteY = 59;
	m_sliding_animation_sprites[13]->spriteWidth = 1511 - 1411;
	m_sliding_animation_sprites[13]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[14]->spriteX = 1519;
	m_sliding_animation_sprites[14]->spriteY = 59;
	m_sliding_animation_sprites[14]->spriteWidth = 1619 - 1519;
	m_sliding_animation_sprites[14]->spriteHeight = 139 - 59;

	m_sliding_animation_sprites[15]->spriteX = 1640;
	m_sliding_animation_sprites[15]->spriteY = 40;
	m_sliding_animation_sprites[15]->spriteWidth = 1727 - 1640;
	m_sliding_animation_sprites[15]->spriteHeight = 139 - 40;

	m_sliding_animation_sprites[16]->spriteX = 1748;
	m_sliding_animation_sprites[16]->spriteY = 40;
	m_sliding_animation_sprites[16]->spriteWidth = 1853 - 1748;
	m_sliding_animation_sprites[16]->spriteHeight = 139 - 40;

	m_sliding_animation_sprites[17]->spriteX = 1856;
	m_sliding_animation_sprites[17]->spriteY = 40;
	m_sliding_animation_sprites[17]->spriteWidth = 1943 - 1856;
	m_sliding_animation_sprites[17]->spriteHeight = 139 - 40;

	m_sliding_animation_sprites[18]->spriteX = 1964;
	m_sliding_animation_sprites[18]->spriteY = 40;
	m_sliding_animation_sprites[18]->spriteWidth = 2051 - 1964;
	m_sliding_animation_sprites[18]->spriteHeight = 139 - 40;

	m_sliding_animation_sprites[19]->spriteX = 2072;
	m_sliding_animation_sprites[19]->spriteY = 40;
	m_sliding_animation_sprites[19]->spriteWidth = 2159 - 2072;
	m_sliding_animation_sprites[19]->spriteHeight = 139 - 40;

	m_sliding_animation_sprites[20]->spriteX = 2180;
	m_sliding_animation_sprites[20]->spriteY = 40;
	m_sliding_animation_sprites[20]->spriteWidth = 2267 - 2180;
	m_sliding_animation_sprites[20]->spriteHeight = 139 - 40;
}

void Player::GenDyingAnimation(){
	for(int i = 0; i < 36; i++){
		m_dying_animation_sprites.push_back(new engine::Sprite());
	}

	m_dying_animation_sprites[0]->spriteX = 4;
	m_dying_animation_sprites[0]->spriteY = 47;
	m_dying_animation_sprites[0]->spriteWidth = 73 - 4;
	m_dying_animation_sprites[0]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[1]->spriteX = 112;
	m_dying_animation_sprites[1]->spriteY = 47;
	m_dying_animation_sprites[1]->spriteWidth = 181 - 112;
	m_dying_animation_sprites[1]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[2]->spriteX = 220;
	m_dying_animation_sprites[2]->spriteY = 47;
	m_dying_animation_sprites[2]->spriteWidth = 289 - 220;
	m_dying_animation_sprites[2]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[3]->spriteX = 328;
	m_dying_animation_sprites[3]->spriteY = 47;
	m_dying_animation_sprites[3]->spriteWidth = 397 - 328;
	m_dying_animation_sprites[3]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[4]->spriteX = 436;
	m_dying_animation_sprites[4]->spriteY = 47;
	m_dying_animation_sprites[4]->spriteWidth = 505 - 436;
	m_dying_animation_sprites[4]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[5]->spriteX = 544;
	m_dying_animation_sprites[5]->spriteY = 47;
	m_dying_animation_sprites[5]->spriteWidth = 613 - 544;
	m_dying_animation_sprites[5]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[6]->spriteX = 652;
	m_dying_animation_sprites[6]->spriteY = 47;
	m_dying_animation_sprites[6]->spriteWidth = 721 - 652;
	m_dying_animation_sprites[6]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[7]->spriteX = 760;
	m_dying_animation_sprites[7]->spriteY = 47;
	m_dying_animation_sprites[7]->spriteWidth = 829 - 760;
	m_dying_animation_sprites[7]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[8]->spriteX = 868;
	m_dying_animation_sprites[8]->spriteY = 47;
	m_dying_animation_sprites[8]->spriteWidth = 937 - 868;
	m_dying_animation_sprites[8]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[9]->spriteX = 976;
	m_dying_animation_sprites[9]->spriteY = 47;
	m_dying_animation_sprites[9]->spriteWidth = 1045 - 976;
	m_dying_animation_sprites[9]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[10]->spriteX = 1084;
	m_dying_animation_sprites[10]->spriteY = 47;
	m_dying_animation_sprites[10]->spriteWidth = 1153 - 1084;
	m_dying_animation_sprites[10]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[11]->spriteX = 1192;
	m_dying_animation_sprites[11]->spriteY = 47;
	m_dying_animation_sprites[11]->spriteWidth = 1261 - 1192;
	m_dying_animation_sprites[11]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[12]->spriteX = 1300;
	m_dying_animation_sprites[12]->spriteY = 47;
	m_dying_animation_sprites[12]->spriteWidth = 1369 - 1300;
	m_dying_animation_sprites[12]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[13]->spriteX = 1408;
	m_dying_animation_sprites[13]->spriteY = 47;
	m_dying_animation_sprites[13]->spriteWidth = 1477 - 1408;
	m_dying_animation_sprites[13]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[14]->spriteX = 1516;
	m_dying_animation_sprites[14]->spriteY = 47;
	m_dying_animation_sprites[14]->spriteWidth = 1585 - 1516;
	m_dying_animation_sprites[14]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[15]->spriteX = 1624;
	m_dying_animation_sprites[15]->spriteY = 47;
	m_dying_animation_sprites[15]->spriteWidth = 1693 - 1624;
	m_dying_animation_sprites[15]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[16]->spriteX = 1732;
	m_dying_animation_sprites[16]->spriteY = 47;
	m_dying_animation_sprites[16]->spriteWidth = 1801 - 1732;
	m_dying_animation_sprites[16]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[17]->spriteX = 1840;
	m_dying_animation_sprites[17]->spriteY = 47;
	m_dying_animation_sprites[17]->spriteWidth = 1909 - 1840;
	m_dying_animation_sprites[17]->spriteHeight = 138 - 47;

	m_dying_animation_sprites[18]->spriteX = 1948;
	m_dying_animation_sprites[18]->spriteY = 47;
	m_dying_animation_sprites[18]->spriteWidth = 2017 - 1948;
	m_dying_animation_sprites[18]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[19]->spriteX = 2056;
	m_dying_animation_sprites[19]->spriteY = 47;
	m_dying_animation_sprites[19]->spriteWidth = 2152 - 2056;
	m_dying_animation_sprites[19]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[20]->spriteX = 2164;
	m_dying_animation_sprites[20]->spriteY = 47;
	m_dying_animation_sprites[20]->spriteWidth = 2233 - 2164;
	m_dying_animation_sprites[20]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[21]->spriteX = 2272;
	m_dying_animation_sprites[21]->spriteY = 47;
	m_dying_animation_sprites[21]->spriteWidth = 2341 - 2272;
	m_dying_animation_sprites[21]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[22]->spriteX = 2380;
	m_dying_animation_sprites[22]->spriteY = 47;
	m_dying_animation_sprites[22]->spriteWidth = 2449 - 2380;
	m_dying_animation_sprites[22]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[23]->spriteX = 2488;
	m_dying_animation_sprites[23]->spriteY = 47;
	m_dying_animation_sprites[23]->spriteWidth = 2557 - 2488;
	m_dying_animation_sprites[23]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[24]->spriteX = 2596;
	m_dying_animation_sprites[24]->spriteY = 47;
	m_dying_animation_sprites[24]->spriteWidth = 2665 - 2596;
	m_dying_animation_sprites[24]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[25]->spriteX = 2704;
	m_dying_animation_sprites[25]->spriteY = 47;
	m_dying_animation_sprites[25]->spriteWidth = 2773 - 2704;
	m_dying_animation_sprites[25]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[26]->spriteX = 2812;
	m_dying_animation_sprites[26]->spriteY = 47;
	m_dying_animation_sprites[26]->spriteWidth = 2881 - 2812;
	m_dying_animation_sprites[26]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[27]->spriteX = 2920;
	m_dying_animation_sprites[27]->spriteY = 47;
	m_dying_animation_sprites[27]->spriteWidth = 2989 - 2920;
	m_dying_animation_sprites[27]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[28]->spriteX = 3028;
	m_dying_animation_sprites[28]->spriteY = 47;
	m_dying_animation_sprites[28]->spriteWidth = 3097 - 3028;
	m_dying_animation_sprites[28]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[29]->spriteX = 3136;
	m_dying_animation_sprites[29]->spriteY = 47;
	m_dying_animation_sprites[29]->spriteWidth = 3205 - 3136;
	m_dying_animation_sprites[29]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[30]->spriteX = 3244;
	m_dying_animation_sprites[30]->spriteY = 47;
	m_dying_animation_sprites[30]->spriteWidth = 3313 - 3244;
	m_dying_animation_sprites[30]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[31]->spriteX = 3352;
	m_dying_animation_sprites[31]->spriteY = 47;
	m_dying_animation_sprites[31]->spriteWidth = 3421 - 3352;
	m_dying_animation_sprites[31]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[32]->spriteX = 3460;
	m_dying_animation_sprites[32]->spriteY = 47;
	m_dying_animation_sprites[32]->spriteWidth = 3529 - 3460;
	m_dying_animation_sprites[32]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[33]->spriteX = 3568;
	m_dying_animation_sprites[33]->spriteY = 47;
	m_dying_animation_sprites[33]->spriteWidth = 3637 - 3568;
	m_dying_animation_sprites[33]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[34]->spriteX = 3676;
	m_dying_animation_sprites[34]->spriteY = 47;
	m_dying_animation_sprites[34]->spriteWidth = 3745 - 3676;
	m_dying_animation_sprites[34]->spriteHeight = 139 - 47;

	m_dying_animation_sprites[35]->spriteX = 3784;
	m_dying_animation_sprites[35]->spriteY = 47;
	m_dying_animation_sprites[35]->spriteWidth = 3853 - 3784;
	m_dying_animation_sprites[35]->spriteHeight = 139 - 47;
}