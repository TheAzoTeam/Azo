#include "player.hpp"

using namespace Azo;


Player::Player(){}

Player::Player(std::string player_name, int x, int y){
	this->game_object_name = player_name;

	// Setting the starting position of the game object.
	this->x = x;
	this->y = y;

	SetPlayerDependencies();
}

void Player::SetPlayerDependencies(){
	CreateAnimations();
	SetAnimations();
	CreateCode();
	SetCode();
}

void Player::CreateAnimations(){
	// Creating a animation controller.
	player_animation_controller = new engine::AnimationController();

	// Creating the player's animation that runs to right looking to right.
	walking_animation = new engine::Animation(
		*this,                                  // Game Object
		"sprites/scottpilgrim_multiple.png",    // Image Path
		900.0f,                                 // Animation Time
		2,                                      // Sprite Rows
		8,                                      // Sprite Colums
		0,                                      // Start Frame
		7);                                     // End Frame

	// Creating the player's animation that runs to right looking to left.
	walking_backwards_animation = new engine::Animation(
		*this,                                                  // Game Object
		"sprites/scottpilgrim_multiple.png",                    // Image Path
		900.0f,                                                 // Animation Time
		2,                                                      // Sprite Rows
		8,                                                      // Sprite Colums
		8,                                                      // Start Frame
		15);                                                    // End frame

	// Creating the player's animation that jump.
	jump_animation = new engine::Animation(
		*this,                                                  // Game Object
		"sprites/scottpilgrim_multiple.png",                    // Image Path
		500.0f,                                                 // Animation Time
		2,                                                      // Sprite Rows
		8,                                                      // Sprite Colums
		5,                                                      // Start Frame
		5);                                                     // End frame

	// Disable Animation Component.
	walking_backwards_animation->DisableComponent();
	jump_animation->DisableComponent();
}

void Player::CreateCode(){
	player_code = new PlayerCode(*this);
}


void Player::SetAnimations(){
	ASSERT(player_animation_controller != NULL, "Player Animation Controller can't be null.");

	// Add all animations to Game Object's Animation Controller's map (Animation name, Animation component).
	player_animation_controller->AddAnimation("walking_foward", *walking_animation);
	player_animation_controller->AddAnimation("walking_backward", *walking_backwards_animation);
	player_animation_controller->AddAnimation("jumping", *jump_animation);


	// Animation Controller is added as a Component to the respective Game Object.
	this->AddComponent(*player_animation_controller);
}

void Player::SetCode(){
	ASSERT(player_code != NULL, "Player Code can't be null.");

	// PlayerCode is added as a component to this GameObject.
	this->AddComponent(*player_code);
}
