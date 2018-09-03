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
			AnimationController(GameObject &gameObject);
			void AddAnimation(std::string animationName, Animation &animation);
			void StartUniqueAnimation(std::string animationName);
			void StartAnimation(std::string animationName);
			void StopAnimation(std::string animationName);
			AnimationState GetAnimationStatus(std::string animationName);
			void Init();
			void shutdown();
			void draw();
			void NextSprite(std::string name);
			inline std::string getClassName(){
				return "AnimationController";
			}
	};

}

#endif
