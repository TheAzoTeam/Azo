#include "animation.hpp"
#include "game.hpp"

using namespace engine;

Animation::Animation(){}

Animation::Animation(GameObject & gameObject, std::string image_path,
		     float animation_time, std::vector<Sprite *> sprite_list,
		     int start_frame, int end_frame, bool loop, double zoom_factor){

	ASSERT(image_path != "", "Animation::CreateAnimation, image_path is empty.");
	ASSERT(animation_time > 0, "Animation time can't be zero or less.");
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");

	this->gameObject = &gameObject;
	this->image_path = image_path;
	this->m_animation_time = animation_time;
	this->m_sprite_list = sprite_list;
	this->m_start_frame = start_frame;
	this->m_end_frame = end_frame;
	this->m_each_frame_time = animation_time / (end_frame - start_frame + 1);
	this->m_current_animation_time = 0.0f;
	this->m_loop = loop;
	this->zoom_factor = zoom_factor;
	this->m_current_sprite = start_frame;
}

Animation::Animation(GameObject & gameObject, std::string image_path,
		     float animation_time, std::vector<Sprite *> sprite_list,
		     int start_frame, int end_frame, bool loop, double zoom_factor,
		     std::pair<double, double> position_relative_to_object){

	ASSERT(image_path != "", "Animation::CreateAnimation, image_path is empty.");
	ASSERT(animation_time > 0, "Animation time can't be zero or less.");
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");

	this->gameObject = &gameObject;
	this->image_path = image_path;
	this->m_animation_time = animation_time;
	this->m_sprite_list = sprite_list;
	this->m_start_frame = start_frame;
	this->m_end_frame = end_frame;
	this->m_each_frame_time = animation_time / (end_frame - start_frame + 1);
	this->m_current_animation_time = 0.0f;
	this->m_loop = loop;
	this->zoom_factor = zoom_factor;
	this->m_current_sprite = start_frame;
	this->m_position_relative_to_object = position_relative_to_object;
}

Animation::~Animation(){}

void Animation::Shutdown(){
	if(m_sprite_list.size() > 0){
		for(auto each_sprite : m_sprite_list){
			delete(each_sprite);
			each_sprite = NULL;
		}
	}
}

void Animation::Draw(){
	// DEBUG("Animation::Draw method.");
	// DEBUG("Checking Limits");
	CheckLimits();
	//DEBUG("Updating Quad");

	UpdateQuad();
	//DEBUG("Updating Measures Limits");

	UpdateGameObjectMeasures();

	//DEBUG("Rendering");
	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		&canvasQuad
		);

	//DEBUG("Current drawing: " << m_current_sprite);
	//DEBUG("Updating frame.");
	UpdateFrameBasedOntime();

}

void Animation::UpdateQuad(){
	// DEBUG("Updating render quad.")
	// DEBUG("Something is wrong here.");
	// DEBUG("m_current_sprite: " << m_current_sprite);
	// DEBUG("m_sprite_list[m_current_sprite]->sprite_x" << m_sprite_list[m_current_sprite]->sprite_x);

	renderQuad = {
		m_sprite_list[m_current_sprite]->sprite_x,
		m_sprite_list[m_current_sprite]->sprite_y,
		m_sprite_list[m_current_sprite]->sprite_width,
		m_sprite_list[m_current_sprite]->sprite_height
	};

	//DEBUG("Updating canvas quad.");

	canvasQuad = {
		(int)(gameObject->m_current_position.first + m_position_relative_to_object.first),
		(int)(gameObject->m_current_position.second + m_position_relative_to_object.second),
		(int)(m_sprite_list[m_current_sprite]->sprite_width * zoom_factor),
		(int)(m_sprite_list[m_current_sprite]->sprite_height * zoom_factor),
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
			m_state = AnimationState::FINISHED;
		}
	}
}

void Animation::UpdateFrameBasedOntime(){
	m_current_animation_time += Game::instance.GetTimer().GetDeltaTime();
	m_current_sprite = m_current_animation_time / m_each_frame_time + m_start_frame;
}


void Animation::UpdateGameObjectMeasures(){
	gameObject->m_half_size.first = m_sprite_list[m_current_sprite]->sprite_width * zoom_factor / 2.0f;
	gameObject->m_half_size.second = m_sprite_list[m_current_sprite]->sprite_height * zoom_factor / 2.0f;

	gameObject->m_center.first = gameObject->m_current_position.first + gameObject->m_half_size.first;

	gameObject->m_center.second = gameObject->m_current_position.second + gameObject->m_half_size.second;
}

void Animation::DisableComponent(){
	this->componentState = State::DISABLED;
	m_current_animation_time = 0.0f;
	m_current_sprite = m_start_frame;
}
