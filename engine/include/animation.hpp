#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include "sdl2include.h"
#include "image_component.hpp"
#include "sprite.hpp"
#include <vector>

namespace engine {

	enum class AnimationState {
		PLAYING,
		STOPPED,
		FINISHED,
	};

	class Animation : public ImageComponent {
	private:
		std::vector<Sprite *> mSpriteList;
		int mCurrentSprite;
		int mStartFrame;
		int mEndFrame;
		float mCurrentAnimationTime;
		int mEachFrameTime;
		float mAnimationTime;
		bool mLoop;

	public:
		std::string animationName;
		AnimationState mState = AnimationState::STOPPED;

	public:
		Animation();
		Animation(GameObject & gameObject, std::string imagePath,
				  float animationTime, std::vector<Sprite *> spriteList,
				  int startFrame, int endFrame, bool loop, double zoomFactor);
		Animation(GameObject & gameObject, std::string imagePath,
				  float animationTime, std::vector<Sprite *> spriteList,
				  int startFrame, int endFrame, bool loop, double zoomFactor,
				  std::pair<double, double> positionRelativeToObject);
		virtual ~Animation();

		void shutdown();
		void draw();
		void disableComponent();
		inline std::string getClassName(){
			return "Animation";
		}

	private:
		void checkLimits();
		void updateQuad();
		void updateFrameBasedOntime();
		void updateGameObjectMeasures();
	};

}

#endif
