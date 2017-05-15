#include "player_code.hpp"

using namespace Azo;


PlayerCode::PlayerCode(){}

void PlayerCode::SetGameObject(engine::GameObject &game_object){
	this->game_object = &game_object;
	this->component_state = engine::State::ENABLED;
	FindAnimationController();
}

void PlayerCode::FindAnimationController(){
	this->anim_controller = *(game_object->GetComponentByType(typeid(engine::AnimationController)));
}

bool PlayerCode::UpdateCode(){
	input_manager.Update();

	if(input_manager.KeyDown(SDL_SCANCODE_W)){
		timer.Step();
		jump = true;
	}

	if(jump){
		timer.DeltaTime();
		if(timer.GetDeltaTime() <= 500.0f){
			INFO("Tempo: " << timer.GetDeltaTime());
			game_object->y -= 10;
		}else{
			jump = false;
		}
	}

	if(input_manager.KeyDown(SDL_SCANCODE_S)){
		game_object->y += 3;
	}

	if(input_manager.KeyDown(SDL_SCANCODE_A)){
		anim_controller.StopAnimation("walking_foward");
		anim_controller.StartAnimation("walking_backward");
	}

	if(input_manager.KeyDown(SDL_SCANCODE_D)){
		anim_controller.StopAnimation("walking_backward");
		anim_controller.StartAnimation("walking_foward");
	}

	game_object->x += 4;
	if(game_object->y <= 150){
		game_object->y += 5;
	}

	if(game_object->x >= engine::Game::instance.sdl_elements.GetWindowWidth()){
		game_object->x = -1 * 108;
	}

	return true;

}
