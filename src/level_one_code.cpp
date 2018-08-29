#include "level_one_code.hpp"

using namespace Azo;

LevelOneCode::LevelOneCode(engine::GameObject &gameObject){
	this->gameObject = &gameObject;
	GetParents();
	FindAudioController();
}

void LevelOneCode::Shutdown(){
	for(auto obstacle : m_obstacle_list){
		obstacle = nullptr;
	}

	mAudioController = nullptr;

	mPlayer = nullptr;
}

void LevelOneCode::FindAudioController(){
	mAudioController = (gameObject->GetAudioController(typeid(engine::AudioController)));
}

void LevelOneCode::GetParents(){
	for(auto parent : gameObject->m_parent_list){
		if(parent->GetClassName() == "Player"){
			mPlayer = dynamic_cast<Player *>(parent);
		}else if(parent->GetClassName() == "Obstacle"){
			m_obstacle_list.push_back(dynamic_cast<Obstacle *>(parent));
		}else if(parent->m_name == "winning_screen"){
			mWinningScreen = parent;
		}else if(parent->m_name == "losing_parts"){
			m_losing_parts = parent;
		}else if(parent->m_name == "losing_death"){
			m_losing_death = parent;
		}else if(parent->m_name == "arrow"){
			mArrow = parent;
		}

	}
}


void LevelOneCode::UpdateCode(){
	//DEBUG("Position: " << gameObject->m_current_position.first );
	//DEBUG("Collected parts: " << mPlayer->m_collected_parts);
	if(mPlayer->m_current_position.first >= 300.0f && gameObject->m_current_position.first > -17600){
		gameObject->m_current_position.first -= 4.0f;
		mPlayer->m_current_position.first = 299;
	}else if(mPlayer->m_current_position.first >= 300.0f){
		m_waiting_time += engine::Game::instance.GetTimer().GetDeltaTime();
		mPlayer->m_speed.first = 0;
		mAudioController->StopAudio("tema_level_one");
		mPlayer->m_state = PlayerState::END;

		if(mPlayer->m_collected_parts != mPlayer->M_TOTAL_PARTS && m_waiting_time >= 10000.0f){
			m_losing_parts->m_object_state = engine::ObjectState::ENABLED;
			ChangeOption();

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
				ChooseOption();
			}

		}else if(mPlayer->m_collected_parts == mPlayer->M_TOTAL_PARTS && m_waiting_time >= 5000.0f){
			mWinningScreen->m_object_state = engine::ObjectState::ENABLED;
			ChangeOption();

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
				ChooseOption();
			}
		}

	}

	UpdateObstaclePosition();

	if(mPlayer->m_state != PlayerState::DIE){
		UpdatePhysics();
	}else{
		m_waiting_time += engine::Game::instance.GetTimer().GetDeltaTime();

		if(m_waiting_time >= 2300.0f){
			m_losing_death->m_object_state = engine::ObjectState::ENABLED;
			ChangeOption();
			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
				ChooseOption();
			}
		}

		if(mAudioController->GetAudioState("tema_level_one") == engine::AudioState::PLAYING){
			mAudioController->StopAudio("tema_level_one");
		}else{
			// Nothing to do.
		}

	}
}

void LevelOneCode::ChangeOption(){
	switch(m_current_option){
		case 1:
			mArrow->m_object_state = engine::ObjectState::ENABLED;

			mArrow->m_current_position = std::make_pair(70, 260);

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)){
				m_current_option = 2;
			}

			break;
		case 2:

			mArrow->m_current_position = std::make_pair(515, 260);

			if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)){
				m_current_option = 1;
			}

			break;
	}
}

void LevelOneCode::ChooseOption(){
	switch(m_current_option){
		case 1:
			mAudioController->StopAllAudios();
			engine::Game::instance.ChangeScene("level_one");
			break;
		case 2:
			engine::Game::instance.ChangeScene("menu");
			break;
	}
}



void LevelOneCode::UpdateObstaclePosition(){
	for(auto each_obstacle : m_obstacle_list){
		each_obstacle->m_current_position.first = gameObject->m_current_position.first + each_obstacle->m_position_relative_to_parent.first;
		each_obstacle->m_current_position.second = gameObject->m_current_position.second + each_obstacle->m_position_relative_to_parent.second;

		for(auto block : each_obstacle->m_block_list){
			block->m_current_position.first = gameObject->m_current_position.first + block->m_position_relative_to_parent.first;
			block->m_current_position.second = gameObject->m_current_position.second + block->m_position_relative_to_parent.second;

			block->m_center.first = block->m_current_position.first + block->m_half_size.first;
			block->m_center.second = block->m_current_position.second + block->m_half_size.second;

			// DEBUG("BLock current position in X: " << block->m_current_position.first);
			// DEBUG("BLock current position in Y: " << block->m_current_position.second);
			// DEBUG("Block center in X: " << block->m_center.first);
			// DEBUG("Block center in Y: " << block->m_center.second);

		}
	}
}

void LevelOneCode::UpdatePhysics(){
	mPlayer->m_current_position.second += mPlayer->m_speed.second * engine::Game::instance.GetTimer().GetDeltaTime();
	double ground_y = 0.0f;
	if(mPlayer->m_speed.second < 0.0f && HasCeiling(&ground_y)){
		mPlayer->m_current_position.second = ground_y + 15;
		mPlayer->m_at_ceiling = true;
	}else if((mPlayer->m_speed.second >= 0.0f || mPlayer->m_state == PlayerState::SLIDE) && HasGround(&ground_y)){
		mPlayer->m_current_position.second = ground_y - mPlayer->m_half_size.second - mPlayer->m_half_size.second + 15;
		mPlayer->m_speed.second = mPlayer->M_ZERO_VECTOR.second;

		mPlayer->m_on_ground = true;

		mPlayer->m_center.first = mPlayer->m_current_position.first + mPlayer->m_half_size.first;
		mPlayer->m_center.second = mPlayer->m_current_position.second + mPlayer->m_half_size.second;

	}else{
		mPlayer->m_on_ground = false;
		mPlayer->m_at_ceiling = false;
	}

	//double delta_walked =  mPlayer->m_speed.first * engine::Game::instance.GetTimer().GetDeltaTime();
	double delta_walked =  mPlayer->m_speed.first;
	// DEBUG("Speed: " << mPlayer->m_speed.first);
	// DEBUG("Delta walked: " << delta_walked);

	mPlayer->m_current_position.first += delta_walked;

	double wall_x = 0.0;

	//Limiting player position on canvas.
	if(mPlayer->m_current_position.first >= 300 && gameObject->m_current_position.first > -7390){
		mPlayer->m_current_position.first = 300;
	}

	if(mPlayer->m_speed.first > 0 &&
	   HasWallOnRight(&wall_x)){
		DEBUG("Collision with the wall");
		mPlayer->m_current_position.first = wall_x - (mPlayer->m_half_size.first * 2);
		mPlayer->m_pushes_left_wall = true;
		mPlayer->m_state = PlayerState::DIE;
	}else{
		mPlayer->m_pushes_left_wall = false;
	}

	if(mPlayer->m_speed.first < 0.0f &&
	   HasWallOnLeft(&wall_x)){
		mPlayer->m_state = PlayerState::DIE;
	}else{
		mPlayer->m_pushes_right_wall = false;
	}
}

bool LevelOneCode::HasGround(double *ground_y){
	std::pair<double, double> player_bottom_left = mPlayer->CalcBottomLeft();
	std::pair<double, double> player_top_right = mPlayer->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;

	for(auto each_obstacle : m_obstacle_list){

		// If the obstacle is a machine part, we check the collision without invisible blocks (since it has animation).
		// If it collides, we return false (so the position isn't updated) and change the state of the machine part.
		// TODO(Roger): Update the collision methods so they return the colliding object.
		// TODO(Roger): Create states to the machine parts.

		if(each_obstacle->m_obstacle_type == ObstacleType::MACHINE_PART){
			std::pair<double, double> block_bottom_left = each_obstacle->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_obstacle->CalcTopRight();

			double block_right = block_top_right.first;
			double block_left = block_bottom_left.first;
			double block_top = block_top_right.second;

			if(player_left <= block_right &&
			   player_right >= block_left &&
			   player_bottom > block_top &&
			   player_top < block_top){

				// Collided.
				each_obstacle->m_machine_part_state = MachinePartState::COLLECTED;
				mPlayer->m_collected_parts++;
				m_obstacle_list.remove(each_obstacle);

				return false;
			}
		}else{
			for(auto each_block : each_obstacle->m_block_list){
				std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
				std::pair<double, double> block_top_right = each_block->CalcTopRight();

				double block_right = block_top_right.first;
				double block_left = block_bottom_left.first;
				double block_top = block_top_right.second;

				// DEBUG("Obstacle: " << each_obstacle->m_name);
				// DEBUG("Player left: " << player_left);
				// DEBUG("Player right: " << player_right);
				// DEBUG("Player top: " << player_top);
				// DEBUG("Player bottom: " << player_bottom);
				// DEBUG("Block left: " << block_left);
				// DEBUG("Block right: " << block_right);
				// DEBUG("Block top: " << block_top);

				if(player_left <= block_right &&
				   player_right >= block_left &&
				   player_bottom > block_top &&
				   player_top < block_top){

					*ground_y = block_top;

					if(each_obstacle->m_obstacle_type == ObstacleType::WESTERN_ROCK ||
					   each_obstacle->m_obstacle_type == ObstacleType::WESTERN_SPIKE ||
					   each_obstacle->m_obstacle_type == ObstacleType::WESTERN_POST){
						mPlayer->m_state = PlayerState::DIE;
					}

					return true;
				}
			}
		}
	}

	return false;
}

bool LevelOneCode::HasWallOnRight(double *wall_x){
	std::pair<double, double> player_bottom_left = mPlayer->CalcBottomLeft();
	std::pair<double, double> player_top_right = mPlayer->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;

	for(auto each_obstacle : m_obstacle_list){

		if(each_obstacle->m_obstacle_type == ObstacleType::MACHINE_PART){
			std::pair<double, double> block_bottom_left = each_obstacle->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_obstacle->CalcTopRight();

			// These magic numbers are used because the walls must be a bit at the front of the top.
			double block_right = block_top_right.first + 5;
			double block_left = block_bottom_left.first - 5;
			double block_top = block_top_right.second + 16;
			double block_bottom = block_bottom_left.second - 16;



			if(player_left < block_left &&
			   player_left < block_right &&
			   player_top <= block_bottom &&
			   player_bottom >= block_top &&
			   player_right >= block_left){

				each_obstacle->m_machine_part_state = MachinePartState::COLLECTED;
				mPlayer->m_collected_parts++;
				m_obstacle_list.remove(each_obstacle);

				return false;
			}
		}else{

			for(auto each_block : each_obstacle->m_block_list){

				std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
				std::pair<double, double> block_top_right = each_block->CalcTopRight();

				// These magic numbers are used because the walls must be a bit at the front of the top.
				double block_right = block_top_right.first + 5;
				double block_left = block_bottom_left.first - 5;
				double block_top = block_top_right.second + 16;
				double block_bottom = block_bottom_left.second - 16;

				// DEBUG("Obstacle: " << each_obstacle->m_name);
				// DEBUG("Game object position x: " << gameObject->m_current_position.first);
				// DEBUG("Game object position y: " << gameObject->m_current_position.second);
				//
				// DEBUG("Obstacle position x: " << each_obstacle->m_current_position.first);
				// DEBUG("Obstacle position y: " << each_obstacle->m_current_position.second);
				//
				// DEBUG("Player left: " << player_left);
				// DEBUG("Player right: " << player_right);
				// DEBUG("Player top: " << player_top);
				// DEBUG("Player bottom: " << player_bottom);
				// DEBUG("Block left: " << block_left);
				// DEBUG("Block right: " << block_right);
				// DEBUG("Block top: " << block_top);
				// DEBUG("Block bottom: " << block_bottom);

				if(player_left < block_left &&
				   player_left < block_right &&
				   player_top <= block_bottom &&
				   player_bottom >= block_top &&
				   player_right >= block_left){

					if(each_obstacle->m_obstacle_type == ObstacleType::WESTERN_POST){
						mPlayer->m_state = PlayerState::DIE;
					}

					*wall_x = block_left - 1.0f;
					return true;
				}

			}
		}
	}

	return false;
}

bool LevelOneCode::HasWallOnLeft(double *wall_x){
	std::pair<double, double> player_bottom_left = mPlayer->CalcBottomLeft();
	std::pair<double, double> player_top_right = mPlayer->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;

	for(auto each_obstacle : m_obstacle_list){

		for(auto each_block : each_obstacle->m_block_list){

			std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_block->CalcTopRight();

			double block_right = block_top_right.first;
			double block_top = block_top_right.second;
			double block_bottom = block_bottom_left.second;


			if(player_left <= block_right &&
			   player_right > block_right &&
			   player_top <= block_bottom &&
			   player_bottom >= block_top){

				*wall_x = block_right + 1.0f;
				return true;
			}

		}
	}

	return false;
}

bool LevelOneCode::HasCeiling(double *ground_y){
	std::pair<double, double> player_bottom_left = mPlayer->CalcBottomLeft();
	std::pair<double, double> player_top_right = mPlayer->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;


	for(auto each_obstacle : m_obstacle_list){

		for(auto each_block : each_obstacle->m_block_list){
			std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
			std::pair<double, double> block_top_right = each_block->CalcTopRight();

			double block_left = block_bottom_left.first;
			double block_right = block_top_right.first;
			double block_top = block_top_right.second;
			double block_bottom = block_bottom_left.second;

			if(player_left >= block_left &&
			   player_right <= block_right &&
			   player_top <= block_bottom &&
			   player_bottom >= block_top &&
			   player_top >= block_top){

				if(each_obstacle->m_obstacle_type == ObstacleType::WESTERN_POST){
					mPlayer->m_state = PlayerState::DIE;
				}

				*ground_y = block_bottom;
				return true;
			}
		}
	}

	return false;

}
