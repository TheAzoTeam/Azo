#include "player.hpp"

using namespace Azo;


Player::Player(){}

Player::Player(std::string player_name){
	this->game_object_name = player_name;
	// Used to create, start as Enable or Disable and set Game Object's animations to Animation Controller.
	this->SetAnimations();
	// Used to send the respective Game Object, that will have this Code Component, to the Code Component.
	this->SetCode();
}

/* Used to create, start as Enable or Disable and set Game Object's animations to Animation Controller.
   At the final of the method the Animation Controller is added as a Component to the respective Game Object. */
void Player::SetAnimations(){
	// Creating the player's animation that runs to right looking to right.
	walking_animation.CreateAnimation(
		*this,                                  // Game Object
		"sprites/scottpilgrim_multiple.png",    // Image Path
		1200.0f,                                // Animation Time
		2,                                      // Sprite Rows
		8,                                      // Sprite Colums
		0,                                      // Start Frame
		7);                                     // End Frame

	// Creating the player's animation that runs to right looking to left.
	walking_backwards_animation.CreateAnimation(
		*this,                                                  // Game Object
		"sprites/scottpilgrim_multiple.png",                    // Image Path
		1200.0f,                                                // Animation Time
		2,                                                      // Sprite Rows
		8,                                                      // Sprite Colums
		8,                                                      // Start Frame
		15);                                                    // End frame

	// Disable de Animation Component.
	walking_backwards_animation.DisableComponent();

	// Add all animations to Game Object's Animation Controller's map (Animation name, Animation component).
	player_animation_controller.AddAnimation("walking_foward", walking_animation);
	player_animation_controller.AddAnimation("walking_backward", walking_backwards_animation);

	// Animation Controller is added as a Component to the respective Game Object.
	this->AddComponent(player_animation_controller);
}

/* Used to send the respective Game Object, that will have this Code Component, to the Code Component.
   At the final of the method the Code Component is added as a Component to the respective Game Object. */
void Player::SetCode(){
	// Set the Game Object to the player code.
	player_code.SetGameObject(*this);

	// Code Component (player code) is added as a Component to the respective Game Object.
	this->AddComponent(player_code);
}
