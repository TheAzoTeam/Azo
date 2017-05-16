#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

#include "animation.hpp"
#include "log.h"

#include <map>
#include <iostream>
namespace engine {

	class AnimationController : public Animation {
		private:
			std::map <std::string, Animation *> animation_map;
		public:
			AnimationController();
			AnimationController(GameObject &game_object);
			void AddAnimation(std::string animation_name, Animation &animation);
			void StartAnimation(std::string animation_name);
			void StopAnimation(std::string animation_name);
			bool Init();
			bool Draw();
			bool Shutdown();

	};

}

#endif
