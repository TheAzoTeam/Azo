#include "animation.hpp"
#include "game.hpp"

using namespace engine;

Animation::Animation(){}

Animation::Animation(GameObject & game_object, std::string image_path,
		     float animation_time, std::vector<Sprite *> sprite_list,
		     int start_frame, int end_frame, bool loop, double zoom_factor){

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
	this->m_current_sprite = start_frame;
}

Animation::Animation(GameObject & game_object, std::string image_path,
		     float animation_time, std::vector<Sprite *> sprite_list,
		     int start_frame, int end_frame, bool loop, double zoom_factor,
		     std::pair<double, double> position_relative_to_object){

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
	this->m_current_sprite = start_frame;
	this->m_position_relative_to_object = position_relative_to_object;
}

Animation::~Animation(){}

void Animation::shutdown(){
	if(m_sprite_list.size() > 0){
		for(auto eachSprite : m_sprite_list){
			delete(eachSprite);
			eachSprite = NULL;
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
	// DEBUG("m_sprite_list[m_current_sprite]->spriteX" << m_sprite_list[m_current_sprite]->spriteX);

	renderQuad = {
		m_sprite_list[m_current_sprite]->spriteX,
		m_sprite_list[m_current_sprite]->spriteY,
		m_sprite_list[m_current_sprite]->spriteWidth,
		m_sprite_list[m_current_sprite]->spriteHeight
	};

	//DEBUG("Updating canvas quad.");

	canvasQuad = {
		(int)(game_object->mCurrentPosition.first + m_position_relative_to_object.first),
		(int)(game_object->mCurrentPosition.second + m_position_relative_to_object.second),
		(int)(m_sprite_list[m_current_sprite]->spriteWidth * zoom_factor),
		(int)(m_sprite_list[m_current_sprite]->spriteHeight * zoom_factor),
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
	game_object->mHalfSize.first = m_sprite_list[m_current_sprite]->spriteWidth * zoom_factor / 2.0f;
	game_object->mHalfSize.second = m_sprite_list[m_current_sprite]->spriteHeight * zoom_factor / 2.0f;

	game_object->mCenter.first = game_object->mCurrentPosition.first + game_object->mHalfSize.first;

	game_object->mCenter.second = game_object->mCurrentPosition.second + game_object->mHalfSize.second;
}

void Animation::disableComponent(){
	this->component_state = State::DISABLED;
	m_current_animation_time = 0.0f;
	m_current_sprite = m_start_frame;
}
