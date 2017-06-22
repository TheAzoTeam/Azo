#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

#include "animation.hpp"
#include "log.h"

#include <map>
#include <iostream>
namespace engine {

	class AnimationController : public Animation {
		private:
			std::map <std::string, Animation *> m_animation_map;
		public:
			AnimationController();
			AnimationController(GameObject &game_object);
			void AddAnimation(std::string animation_name, Animation &animation);
			void StartAnimation(std::string animation_name);
			void StopAnimation(std::string animation_name);
			void Init();
			void Shutdown();
			void Draw();
			void NextSprite(std::string name);
			inline std::string GetClassName(){
				return "AnimationController";
			}
	};

}

#endif
