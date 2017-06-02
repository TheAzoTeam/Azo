#include "player_code.hpp"
#include "level_manager.hpp"


using namespace Azo;

PlayerCode::PlayerCode(){}

PlayerCode::PlayerCode(engine::GameObject &game_object){
	this->game_object = &game_object;
	this->component_state = engine::State::ENABLED;
	this->state = PlayerState::FALLING;
	FindAnimationController();
}

void PlayerCode::FindAnimationController(){
	this->anim_controller = *(game_object->GetAnimationController(typeid(engine::AnimationController)));
}

void PlayerCode::UpdateCode(){
	//DEBUG("Updating player code.");

	if(state != PlayerState::JUMPING){
		state = PlayerState::FALLING;
		CheckCollisionWithFloor();
	}

	CheckCollisionWithWall();

	// The player should jump (INPUT = 'W').
	if(engine::Game::instance.input_manager.KeyDown(engine::Button::W) && this->state == PlayerState::RUNNING){
		timer.Step();
		this->state = PlayerState::JUMPING;
		anim_controller.StartAnimation("jumping");
		anim_controller.StopAnimation("walking_foward");
		anim_controller.StopAnimation("walking_backward");
	}

	if(this->state == PlayerState::JUMPING){
		timer.DeltaTime();
		if(timer.GetDeltaTime() <= 350.0f){
			//INFO("Tempo: " << timer.GetDeltaTime());
			game_object->y -= 13;
		}else{
			this->state = PlayerState::FALLING;
		}
	}

	if(this->state == PlayerState::RUNNING){
		anim_controller.StopAnimation("jumping");
		anim_controller.StartAnimation("walking_foward");
	}

	// The player should slide (INPUT = 'S').
	if(engine::Game::instance.input_manager.KeyDown(engine::Button::S)){
		//game_object->y += 3;
	}

	// Gravity that pulls the player down.
	if(state != PlayerState::RUNNING){
		//DEBUG("Gravity!");
		game_object->y += 6;
	}

	// // Verify if the player stopped to fall.
	// if(game_object->y >= 380){
	//      this->state = PlayerState::RUNNING;
	// }

	// Stop the player almost in the center of the page
	if(game_object->x < engine::Game::instance.sdl_elements.GetWindowWidth() / 3){
		Run();
	}


}

void PlayerCode::Run(){
	// Continuous run to right.
	game_object->x += 4;

}


void PlayerCode::CheckCollisionWithFloor(){
	std::list<std::string>::iterator it;

	for(it = game_object->collision_list.begin(); it != game_object->collision_list.end(); ++it){
		auto collision = *it;
		if(collision == "floor" || collision == "floor_2"){
			state = PlayerState::RUNNING;
			game_object->collision_list.erase(it);
			break;
		}
	}

	//DEBUG("List after clear: " << game_object->collision_list.size());

}

void PlayerCode::CheckCollisionWithWall(){
	std::list<std::string>::iterator it;

	for(it = game_object->collision_list.begin(); it != game_object->collision_list.end(); ++it){
		auto collision = *it;
		if(collision == "wall"){
			game_object->collision_list.erase(it);
			LevelManager::level_manager.GoToMenu();
			break;
		}
	}

//	DEBUG("List after clear: " << game_object->collision_list.size());
}

