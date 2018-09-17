#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

#include "animation.hpp"
#include "log.h"

#include <map>
#include <iostream>
namespace engine {

	class AnimationController : public Animation {
		private:
			std::map <std::string, Animation *> mAnimationMap;
		public:
			AnimationController();
			AnimationController(GameObject &game_object);
			void addAnimation(std::string animationName, Animation &animation);
			void startUniqueAnimation(std::string animationName);
			void startAnimation(std::string animationName);
			void stopAnimation(std::string animationName);
			AnimationState getAnimationStatus(std::string animationName);
			void init();
			void shutdown();
			void draw();
			void nextSprite(std::string name);
			inline std::string getClassName(){
				return "AnimationController";
			}
	};

}

#endif
