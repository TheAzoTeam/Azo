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

	//player.AddComponent(walking_animation);

	walking_backwards_animation.CreateAnimation(
		player,                                                 // Game Object
		"sprites/scottpilgrim_multiple.png",                    // Imagem Path
		1200.0f,                                                // Animation Time
		2,                                                      // Sprite Rows
		8,                                                      // Sprite Colums
		8,                                                      // Start Frame
		15);                                                    // End frame

	walking_backwards_animation.DisableComponent();

	player_animation_controller.AddAnimation("walking_foward", walking_animation);
	player_animation_controller.AddAnimation("walking_backward", walking_backwards_animation);

	player.AddComponent(player_animation_controller);
}

void Player::SetCode(Player &player){
	player_code.SetGameObject(player);
	player_code.FindAnimationController();
	player.AddComponent(player_code);
}

