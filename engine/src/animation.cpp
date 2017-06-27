#include "animation.hpp"
#include "game.hpp"

using namespace engine;

Animation::Animation(){}

Animation::Animation(GameObject & game_object, std::string image_path,
		     float animation_time, std::vector<Sprite *> sprite_list,
		     int start_frame, int end_frame, bool loop, int zoom_factor){

	ASSERT(image_path != "", "Animation::CreateAnimation, image_path is empty.");
	ASSERT(animation_time > 0, "Animation time can't be zero or less.");
	ASSERT(&game_object != NULL, "The game_object can't be null.");

	this->game_object = &game_object;
	this->image_path = image_path;
	this->m_animation_time = animation_time;
	this->m_sprite_list = sprite_list;
	this->m_start_frame = start_frame;
	this->m_end_frame = end_frame;
	this->m_each_frame_time = animation_time / (end_frame - start_frame + 1);
	this->m_current_animation_time = 0.0f;
	this->m_loop = loop;
	this->zoom_factor = zoom_factor;
}

Animation::~Animation(){}

void Animation::Draw(){
	//DEBUG("Animation::Draw method.");
	CheckLimits();
	UpdateQuad();
	UpdateGameObjectMeasures();

	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		&canvasQuad
		);

	//DEBUG("Current drawing: " << m_current_sprite);

	UpdateFrameBasedOntime();

}

void Animation::UpdateQuad(){
	renderQuad = {
		m_sprite_list[m_current_sprite]->sprite_x,
		m_sprite_list[m_current_sprite]->sprite_y,
		m_sprite_list[m_current_sprite]->sprite_width,
		m_sprite_list[m_current_sprite]->sprite_height
	};

	canvasQuad = {
		(int)game_object->m_current_position.first,
		(int)game_object->m_current_position.second,
		m_sprite_list[m_current_sprite]->sprite_width * zoom_factor,
		m_sprite_list[m_current_sprite]->sprite_height * zoom_factor
	};
}

void Animation::CheckLimits(){
	if(m_current_sprite > m_end_frame){
		if(m_loop){
			m_current_sprite = 0;
			m_current_animation_time = 0.0f;
			m_state = AnimationState::STOPPED;
		}else{
			m_current_sprite = m_end_frame;
		}
	}
}

void Animation::UpdateFrameBasedOntime(){
	m_current_animation_time += Game::instance.GetTimer().GetDeltaTime();
	m_current_sprite = m_current_animation_time / m_each_frame_time + m_start_frame;
}


void Animation::UpdateGameObjectMeasures(){
	game_object->m_half_size.first = m_sprite_list[m_current_sprite]->sprite_width * zoom_factor / 2.0f;
	game_object->m_half_size.second = m_sprite_list[m_current_sprite]->sprite_height * zoom_factor / 2.0f;

	game_object->m_center.first = game_object->m_current_position.first + game_object->m_half_size.first;

	game_object->m_center.second = game_object->m_current_position.second + game_object->m_half_size.second;
}

void Animation::DisableComponent(){
	this->component_state = State::DISABLED;
	m_current_animation_time = 0.0f;
	m_current_sprite = m_start_frame;
}
