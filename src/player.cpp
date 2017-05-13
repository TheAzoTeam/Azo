#include "player.hpp"

using namespace Azo;

Player::Player(){}

Player::Player(std::string player_name){
	this->game_object_name = player_name;
}

void Player::SetAnimations(Player &player){
	walking_animation.CreateAnimation(
		player,                                 // Game Object
		"sprites/scottpilgrim_multiple.png",    // Imagem Path
		1200.0f,                                // Animation Time
		2,                                      // Sprite Rows
		8,                                      // Sprite Colums
		0,                                      // Start Frame
		7);                                     // End Frame

	player.AddComponent(walking_animation);
}

void Player::SetCode(Player &player){
	jumping_code.SetGameObject(player);
	player.AddComponent(jumping_code);
}

