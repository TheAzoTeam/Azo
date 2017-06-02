#include "animation.hpp"
#include "game.hpp"

using namespace engine;


Animation::Animation(){}

Animation::Animation(GameObject & game_object, std::string image_path, float animation_time, std::vector<Sprite *> sprite_list, int start_frame, int end_frame){

	ASSERT(image_path != "", "Animation::CreateAnimation, image_path is empty.");
	ASSERT(animation_time > 0, "Animation time can't be zero or less.");
	ASSERT(&game_object != NULL, "The game_object can't be null.");

	this->game_object = &game_object;
	this->image_path = image_path;
	this->animation_time = animation_time;
	this->sprite_list = sprite_list;
	this->start_frame = start_frame;
	this->end_frame = end_frame;
	this->each_frame_time = animation_time / (end_frame - start_frame + 1);
	this->current_animation_time = 0.0f;
}

Animation::~Animation(){}

void Animation::Draw(){
	UpdateFrameBasedOntime();
	UpdateQuad();
	UpdateGameObjectMeasures();
	CheckLimits();

	int successful_draw = SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		&canvasQuad
		);

	if(successful_draw < 0){
		ERROR("Unable to Draw.");
	}

}

void Animation::UpdateQuad(){
	renderQuad = {
		sprite_list[current_sprite]->sprite_x,
		sprite_list[current_sprite]->sprite_y,
		sprite_list[current_sprite]->sprite_width,
		sprite_list[current_sprite]->sprite_height
	};

	canvasQuad = {
		BackgroundComponent::game_object->x,
		BackgroundComponent::game_object->y,
		sprite_list[current_sprite]->sprite_width,
		sprite_list[current_sprite]->sprite_height
	};
}

void Animation::CheckLimits(){
	current_sprite++;

	if(current_sprite > end_frame){
		current_sprite = 0;
		current_animation_time = 0.0f;
	}
}

void Animation::UpdateFrameBasedOntime(){
	current_animation_time += Game::instance.GetTimer().GetDeltaTime();
	current_sprite = current_animation_time / each_frame_time + start_frame;
}


void Animation::UpdateGameObjectMeasures(){
	// Before drawing, set the GameObject sizes so we can calculate collision.
	game_object->game_object_width = sprite_list[current_sprite]->sprite_width;

	game_object->game_object_height = sprite_list[current_sprite]->sprite_height;

	game_object->left = game_object->x;
	game_object->right = game_object->x + game_object->game_object_width;
	game_object->top = game_object->y;
	game_object->bottom = game_object->y + game_object->game_object_height;

}

