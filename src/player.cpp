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
	int width = 0;

	INFO("Entering Create Animations");
	for(int i = 0; i < 16; i++){
		sprite_list.push_back(new engine::Sprite());
	}


	for(int i = 0; i < 8; i++){
		sprite_list[i]->sprite_x = width;
		sprite_list[i]->sprite_y = 0;
		sprite_list[i]->sprite_width = 108;
		sprite_list[i]->sprite_height = 140;
		width += 108;
	}

	width = 0;
	for(int i = 8; i < 16; i++){
		sprite_list[i]->sprite_x = width;
		sprite_list[i]->sprite_y = 108;
		sprite_list[i]->sprite_width = 108;
		sprite_list[i]->sprite_height = 280;
		width += 108;
	}

	// Creating a animation controller.
	player_animation_controller = new engine::AnimationController();

	DEBUG("Creating walking animation.");
	// Creating the player's animation that runs to right looking to right.
	walking_animation = new engine::Animation(
		*this,                                                                  // Game Object
		"sprites/scottpilgrim_multiple.png",                                    // Image Path
		900.0f,                                                                 // Animation Time
		sprite_list,
		0,
		7
		);

	DEBUG("Finished creating walking animation.");

	// Creating the player's animation that runs to right looking to left.
	walking_backwards_animation = new engine::Animation(
		*this,                                                  // Game Object
		"sprites/scottpilgrim_multiple.png",                    // Image Path
		900.0f,                                                 // Animation Time
		sprite_list,
		8,
		15
		);

	// Creating the player's animation that jump.
	jump_animation = new engine::Animation(
		*this,                                                  // Game Object
		"sprites/scottpilgrim_multiple.png",                    // Image Path
		500.0f,                                                 // Animation Time
		sprite_list,
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
	ASSERT(player_animation_controller != NULL, "Player Animation Controller can't be null when setting animations.");
	ASSERT(walking_animation != NULL, "Walking animation can't be null when setting animations.");
	ASSERT(walking_backwards_animation != NULL, "Walking backwards animation can't be null when setting animations.");
	ASSERT(jump_animation != NULL, "Jump animation can't be null when setting animations.");

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

void Player::Shutdown(){
	INFO("Shutting down player.");
	DestroyComponents();
}

void Player::DestroyComponents(){
	INFO("Destroying components.");

	ASSERT(walking_animation != NULL, "Walking animation can't be NULL when shutting down.");
	ASSERT(walking_backwards_animation != NULL, "Walking backwards animation can't be NULL when shutting down.");
	ASSERT(jump_animation != NULL, "Jump animation can't be NULL when shutting down.");

	walking_animation->Shutdown();
	free(walking_animation);
	walking_animation = NULL;

	walking_backwards_animation->Shutdown();
	free(walking_backwards_animation);
	walking_backwards_animation = NULL;

	jump_animation->Shutdown();
	free(jump_animation);
	jump_animation = NULL;
}

