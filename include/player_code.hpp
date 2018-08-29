#ifndef PLAYER_CODE
#define PLAYER_CODE

#include "code_component.hpp"
#include "animation_controller.hpp"

namespace Azo {
	class Player;

	class PlayerCode : public engine::CodeComponent {
		private:
			Player *mPlayer = nullptr;
			engine::AnimationController *mAnimationController = nullptr;
			engine::AudioController *mAudioController = nullptr;

			void UpdateCode();
			void UpdatePhysics();
			void FindAnimationController();
			void FindAudioController();

		public:
			PlayerCode();
			virtual ~PlayerCode();
			PlayerCode(Player *player);
			void Shutdown();
	};
}

#endif
