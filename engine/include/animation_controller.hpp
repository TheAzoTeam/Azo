#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

/*************************************
@file animation.hpp
@brief Purpose: Controls animaton.

GPL v3.0 License
Copyright (c) 2017 Azo

Notice: TheAzo, TheAzoTeam
https://github.com/TecProg2018-2/Azo

This file implements the main game component its declaration and state.
*************************************/
#include "animation.hpp"
/**
 * @file log.h
 * @brief Purpose: Contains general scope to the log.
 *
 * GLP v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "log.h"

#include <map>
#include <iostream>
namespace engine {

	class AnimationController : public Animation {
		/**
	     * @brief An Animation controller class.
	  	 *
	     * Generic Component class.
		 * It's how the engine'll controll how animation works.
	    */
		private:
			std::map <std::string, Animation *> mAnimationMap;
		public:
			AnimationController();

			AnimationController(GameObject &gameObject);
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
