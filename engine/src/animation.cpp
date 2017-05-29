#include "animation.hpp"
#include "game.hpp"

using namespace engine;


Animation::Animation(){}

void Animation::CreateAnimation(
	GameObject & game_object,
	std::string image_path,
	float animation_time,
	int sprite_rows,
	int sprite_colums,
	int starting_frame,
	int ending_frame){

	ASSERT(image_path != "", "Animation::CreateAnimation, image_path is empty.");
	ASSERT(animation_time > 0, "Animation time can't be zero or less.");
	ASSERT(sprite_rows >= 0, "The number of rows in a sprite can't be less than zero.");
	ASSERT(sprite_colums >= 0, "The number of colums in a sprite can't be less than zero.");
	ASSERT(starting_frame >= 0, "The starting frame in a animation can't be less than zero.");
	ASSERT(ending_frame > 0, "THe ending frame in a animation can't be zero or less.");
	ASSERT(&game_object != NULL, "The game_object can't be null.");

	this->game_object = &game_object;
	this->image_path = image_path;
	this->animation_name = animation_name;

	this->animation_time = animation_time;
	this->sprite_rows = sprite_rows;
	this->sprite_colums = sprite_colums;
	this->starting_frame = starting_frame;
	this->ending_frame = ending_frame;
	this->total_frames = ending_frame - starting_frame + 1;
	this->frame_time = animation_time / total_frames;
	this->current_animation_time = 0.0;
}

Animation::~Animation(){}

bool Animation::Draw(){
//	DEBUG("Animation::Draw()");
	this->frame_width = this->component_width / sprite_colums;
	this->frame_height = this->component_height / sprite_rows;
//	DEBUG("Component width: " << this->component_height);
	current_animation_time += Game::instance.GetTimer().GetDeltaTime();
	current_frame = current_animation_time / frame_time + starting_frame;


	//DEBUG("Current Frame:" << current_frame);
	int Y = current_frame / (this->component_width / frame_width);
	int X = current_frame % (this->component_width / frame_width);

	ImageComponent::renderQuad = {X*frame_width, Y * frame_height, frame_width, frame_height};

	ImageComponent::canvasQuad = {
		ImageComponent::game_object->x,
		ImageComponent::game_object->y,
		frame_width,
		frame_height
	};

	if(current_frame >= ending_frame){
		current_frame = starting_frame;
		current_animation_time = 0;
	}

	ImageComponent::Draw();

	return true;
}
