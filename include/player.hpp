#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "game_object.hpp"
#include "animation.hpp"
#include "player_code.hpp"
#include "animation_controller.hpp"


namespace Azo {

	class Player : public engine::GameObject {
		public:
			// Used to manage the play's animations.
			engine::AnimationController player_animation_controller;

		private:
			// The player's animation.
			engine::Animation walking_animation;
			// The player's animation.
			engine::Animation walking_backwards_animation;
			// The player's motion code.
			PlayerCode player_code;

		public:
			Player();

			Player(std::string player_name);

			/* Used to create, start as Enable or Disable and set Game Object's animations to Animation Controller.
			   At the final of the method the Animation Controller is added as a Component to the respective Game Object. */
			void SetAnimations();

			/* Used to send the respective Game Object, that will have this Code Component, to the Code Component.
			   At the final of the method the Code Component is added as a Component to the respective Game Object. */
			void SetCode();
	};

}

#endif
