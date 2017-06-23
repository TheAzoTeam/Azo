#include "player_code.hpp"
#include "game.hpp"
#include "player.hpp"

using namespace Azo;

PlayerCode::PlayerCode(){}

PlayerCode::PlayerCode(engine::GameObject &game_object){
	m_player = dynamic_cast<Player *>(&game_object);
	m_player->m_state = PlayerState::WALK;
	m_player->m_on_ground = true;
	FindAnimationController();
}

void PlayerCode::FindAnimationController(){
	//DEBUG("PlayerCode::FindAnimationController method.");
	m_animation_controller = (m_player->GetAnimationController(typeid(engine::AnimationController)));
}

void PlayerCode::UpdateCode(){
	switch(m_player->m_state){
		case PlayerState::WALK:

			m_animation_controller->StartAnimation("walking");

			m_player->m_walking_right = true;

			if(m_player->m_pushes_right_wall || m_player->m_pushes_left_wall){
				//DEBUG("Update code method. Player Speed in X: " << m_player->m_speed.first);
				m_player->m_speed.first = m_player->M_ZERO_VECTOR.first;
			}else{
				m_player->m_speed.first = m_player->M_WALKING_SPEED;
				//DEBUG("PLAYER SHOULD HAVE SPEED! PLAYER SPEED " << m_player->m_speed.first);
			}

			if(engine::Game::instance.input_manager.KeyState(engine::Button::W)){
				DEBUG("W pressed!");
				m_player->m_speed.second = m_player->M_JUMPING_SPEED; // Jumping speed.
				m_player->m_state = PlayerState::JUMP;
			}else if(!m_player->m_on_ground){
				//DEBUG("Player isn't on ground. (WALK)");
				m_player->m_state = PlayerState::JUMP;
			}

			break;

		case PlayerState::JUMP:

			if(m_player->m_on_ground){
				m_player->m_state = PlayerState::WALK;
				m_player->m_walking_right = true;
			}

			m_animation_controller->StartAnimation("jumping");

			m_player->m_speed.second += (m_player->M_GRAVITY * engine::Game::instance.GetTimer().GetDeltaTime());
			//DEBUG("UpdateCode method. Player Speed in Y: " << m_player->m_speed.second);

			if(m_player->m_pushes_right_wall){
				m_player->m_speed.first = m_player->M_ZERO_VECTOR.first;
			}else{
				m_player->m_speed.first = m_player->M_WALKING_SPEED;         // Walking speed.
			}

			if(m_player->m_pushes_left_wall){
				m_player->m_speed.first = m_player->M_ZERO_VECTOR.first;
			}

			break;
	}

	UpdatePhysics();
}

void PlayerCode::UpdatePhysics(){

	m_player->m_old_position = m_player->m_current_position;
	m_player->m_old_speed = m_player->m_speed;

	m_player->m_was_on_ground = m_player->m_on_ground;
	m_player->m_pushed_right_wall = m_player->m_pushes_right_wall;
	m_player->m_pushed_left_wall = m_player->m_pushed_left_wall;
	m_player->m_was_at_ceiling = m_player->m_at_ceiling;

	double delta_walked =  m_player->m_speed.first * engine::Game::instance.GetTimer().GetDeltaTime();

	m_player->m_current_position.first += delta_walked;
	double wall_x = 0.0;

	//Limiting player position on canvas.
	if(m_player->m_current_position.first >= 300){
		m_player->m_current_position.first = 300;
	}

	if(HasWallOnRight(&wall_x)){
		//DEBUG("Collision with the wall");
		//DEBUG("Wall x: " << wall_x);
		m_player->m_current_position.first = wall_x - (m_player->m_half_size.first * 2);
		m_player->m_pushes_left_wall = true;
	}else{
		m_player->m_pushes_left_wall = false;
	}

	if(HasWallOnLeft(&wall_x)){
		m_player->m_current_position.first = wall_x;
		m_player->m_pushes_right_wall = true;
	}else{
		m_player->m_pushes_right_wall = false;
	}

	//DEBUG("UpdatePhysics method. Player Speed in X: " << m_player->m_speed.first);
	//DEBUG("UpdatePhysics method. Player Position in X: " << m_player->m_current_position.first);

	// If position.second goes up, the character goes down on canvas.
	m_player->m_current_position.second += m_player->m_speed.second * engine::Game::instance.GetTimer().GetDeltaTime();
	//DEBUG("Player Speed in Y: " << m_player->m_speed.second);
	//DEBUG("Before Collision Check. Player Position in Y: " << m_player->m_current_position.second);
	double ground_y = 0.0f;
	if(m_player->m_speed.second < 0.0f && HasCeiling(&ground_y)){
		//DEBUG("Has CEILING!");
		m_player->m_current_position.second = ground_y + 15;
		m_player->m_at_ceiling = true;
	}else if(m_player->m_speed.second >= 0.0f && HasGround(&ground_y)){
		//DEBUG("Collision.");
		//DEBUG("Ground y: " << ground_y);
		m_player->m_current_position.second = ground_y - (m_player->m_half_size.second * 2.0f) + 15;
		m_player->m_on_ground = true;
	}else if(m_player->m_current_position.second >= 300.0f){
		m_player->m_current_position.second = 300.0f;
		//DEBUG("UpdatePhysics method.  Setting m_on_ground to true");
		m_player->m_on_ground = true;
		m_player->m_at_ceiling = false;
	}else{
		//DEBUG("UpdatePhysics method. Setting m_on_ground to false.");
		m_player->m_on_ground = false;
		m_player->m_at_ceiling = false;
	}

//DEBUG("Player Position in Y: " << m_player->m_current_position.second);
//DEBUG("Update Physics END.");
}

bool PlayerCode::HasGround(double *ground_y){
	// std::pair<double, double> player_bottom_left = m_player->CalcBottomLeft();
	// std::pair<double, double> player_bottom_right = m_player->CalcBottomRight();
	// std::pair<double, double> player_top_right = m_player->CalcTopRight();
	// for(auto each_block : m_player->m_block_list){
	//
	//      std::pair<double, double> block_top_left = each_block->CalcTopLeft();
	//      std::pair<double, double> block_top_right = each_block->CalcTopRight();
	//
	//      if(player_bottom_left.first <= block_top_right.first && player_bottom_right.first >= block_top_left.first){
	//
	//              if(player_bottom_right.first < block_top_left.first){
	//                      return false;
	//              }
	//
	//              if(player_bottom_left.second < block_top_left.second){
	//                      return false;
	//              }
	//
	//              if(player_top_right.second > block_top_right.second){
	//                      return false;
	//              }
	//
	//              *ground_y = block_top_left.second;
	//
	//              return true;
	//      }
	// }

	return false;
}

bool PlayerCode::HasWallOnRight(double *wall_x){
	DEBUG("Block list: " << m_player->m_block_list.size());
	std::pair<double, double> player_bottom_left = m_player->CalcBottomLeft();
	std::pair<double, double> player_top_right = m_player->CalcTopRight();

	double player_top = player_top_right.second;
	double player_bottom = player_bottom_left.second;
	double player_left = player_bottom_left.first;
	double player_right = player_top_right.first;

	for(auto each_block : m_player->m_block_list){

		std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
		std::pair<double, double> block_top_right = each_block->CalcTopRight();

		double block_right = block_top_right.first;
		double block_left = block_bottom_left.first;
		double block_top = block_top_right.second;
		double block_bottom = block_bottom_left.second;

		if(player_left < block_left && player_left < block_right){

			if(player_top > block_bottom){
				return false;
			}

			if(player_bottom < block_top){
				return false;
			}

			if(player_right < block_left - 1){
				return false;
			}

			*wall_x = block_left - 1.0f;
			return true;
		}
	}

	return false;
}

bool PlayerCode::HasWallOnLeft(double *wall_x){
	// std::pair<double, double> player_bottom_left = m_player->CalcBottomLeft();
	// std::pair<double, double> player_top_right = m_player->CalcTopRight();
	//
	// double player_top = player_top_right.second;
	// double player_bottom = player_bottom_left.second;
	// double player_left = player_bottom_left.first;
	// double player_right = player_top_right.first;
	//
	// for(auto each_block : m_player->m_block_list){
	//
	//      std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
	//      std::pair<double, double> block_top_right = each_block->CalcTopRight();
	//
	//      double block_right = block_top_right.first;
	//
	//      if(player_left <= block_right){
	//
	//              double block_top = block_top_right.second;
	//              double block_bottom = block_bottom_left.second;
	//
	//              if(player_top > block_bottom){
	//                      return false;
	//              }
	//
	//              if(player_bottom < block_top){
	//                      return false;
	//              }
	//
	//              if(player_right > block_right + 1){
	//                      *wall_x = block_right + 1.0f;
	//                      return true;
	//              }
	//      }
	//
	// }

	return false;
}

bool PlayerCode::HasCeiling(double *ground_y){
	// std::pair<double, double> player_bottom_left = m_player->CalcBottomLeft();
	// std::pair<double, double> player_top_right = m_player->CalcTopRight();
	//
	// double player_top = player_top_right.second;
	// double player_bottom = player_bottom_left.second;
	// double player_left = player_bottom_left.first;
	// double player_right = player_top_right.first;
	//
	//
	// for(auto each_block : m_player->m_block_list){
	//      std::pair<double, double> block_bottom_left = each_block->CalcBottomLeft();
	//      std::pair<double, double> block_top_right = each_block->CalcTopRight();
	//
	//      double block_left = block_bottom_left.first;
	//      double block_right = block_top_right.first;
	//
	//      if(player_left >= block_left && player_right <= block_right){
	//
	//              double block_top = block_top_right.second;
	//              double block_bottom = block_bottom_left.second;
	//
	//              DEBUG("Player top: " << player_top);
	//              DEBUG("Player bottom: " << player_bottom);
	//              DEBUG("Block top: " << block_top);
	//              DEBUG("Block_bottom: " << block_bottom);
	//
	//              if(player_top > block_bottom){
	//                      return false;
	//              }
	//
	//              if(player_bottom < block_top){
	//                      return false;
	//              }
	//
	//              if(player_top < block_bottom && player_top > block_top){
	//                      *ground_y = block_bottom;
	//                      return true;
	//              }
	//      }
	// }

	return false;

}