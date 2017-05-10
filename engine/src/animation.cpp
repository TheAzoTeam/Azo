#include "animation.hpp"
#include "game.hpp"

using namespace engine;


Animation::Animation(){}

Animation::Animation(
	GameObject & game_object,
	std::string image_path,
	float animation_time,
	int sprite_rows,
	int sprite_colums,
	int starting_frame,
	int ending_frame){

	INFO("Starting Animation Constructor.");
	this->game_object = &game_object;
	this->image_path = image_path;

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

void Animation::UpdateAnimation(){
	frame_width = component_width / sprite_colums;
	frame_height = component_height / sprite_rows;

	current_animation_time += Game::instance.GetTimer().GetDeltaTime();
	current_frame = current_animation_time / frame_time + starting_frame;

	//DEBUG("Current Frame:" << current_frame);
	int Y = current_frame / (component_width / frame_width);
	int X = current_frame % (component_width / frame_width);

	renderQuad = {X*frame_width, Y * frame_height, frame_width, frame_height};

	canvasQuad = {
		game_object->x,
		game_object->y,
		frame_width,
		frame_height
	};

	if(current_frame >= ending_frame){
		current_frame = starting_frame;
		current_animation_time = 0;
	}

	ImageComponent::Draw();
}
