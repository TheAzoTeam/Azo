#include "player_jumping_code.hpp"

using namespace Azo;

PlayerJumpingCode::PlayerJumpingCode(){}

void PlayerJumpingCode::SetGameObject(engine::GameObject & game_object){
	this->game_object = &game_object;
}



bool PlayerJumpingCode::UpdateCode(){
	INFO("Updating player code.");
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


	game_object->x += 4;
	if(game_object->y <= 150){
		game_object->y += 5;
	}


	if(game_object->x >= engine::Game::instance.sdl_elements.GetWindowWidth()){
		game_object->x = -1 * 108;
	}

	return true;

}