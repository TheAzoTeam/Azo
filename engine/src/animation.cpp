#include "animation.hpp"
#include "game.hpp"

using namespace engine;

Animation::Animation(){}

Animation::Animation(GameObject & gameObject, std::string imagePath,
					 float animationTime, std::vector<Sprite *> spriteList,
					 int startFrame, int endFrame, bool loop, double zoomFactor){
	ASSERT(imagePath != "", "Animation::CreateAnimation, imagePath is empty.");
	ASSERT(animationTime > 0, "Animation time can't be zero or less.");
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");

	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->mAnimationTime = animationTime;
	this->mSpriteList = spriteList;
	this->mStartFrame = startFrame;
	this->mEndFrame = endFrame;
	this->mEachFrameTime = animationTime / (endFrame - startFrame + 1);
	this->mCurrentAnimationTime = 0.0f;
	this->mLoop = loop;
	this->zoomFactor = zoomFactor;
	this->mCurrentSprite = startFrame;
}

Animation::Animation(GameObject & gameObject, std::string imagePath,
					 float animationTime, std::vector<Sprite *> spriteList,
					 int startFrame, int endFrame, bool loop, double zoomFactor,
					 std::pair<double, double> positionRelativeToObject){
	ASSERT(imagePath != "", "Animation::CreateAnimation, imagePath is empty.");
	ASSERT(animationTime > 0, "Animation time can't be zero or less.");
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");

	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->mAnimationTime = animationTime;
	this->mSpriteList = spriteList;
	this->mStartFrame = startFrame;
	this->mEndFrame = endFrame;
	this->mEachFrameTime = animationTime / (endFrame - startFrame + 1);
	this->mCurrentAnimationTime = 0.0f;
	this->mLoop = loop;
	this->zoomFactor = zoomFactor;
	this->mCurrentSprite = startFrame;
	this->mPositionRelativeToObject = positionRelativeToObject;
}

Animation::~Animation(){}

void Animation::shutdown(){
	if(mSpriteList.size() > 0){
		for(auto eachSprite : mSpriteList){
			delete(eachSprite);
			eachSprite = NULL;
		}
	}
}

void Animation::draw(){
	// DEBUG("Animation::draw method.");
	// DEBUG("Checking Limits");
	checkLimits();
	//DEBUG("Updating Quad");

	updateQuad();
	//DEBUG("Updating Measures Limits");

	updateGameObjectMeasures();

	//DEBUG("Rendering");
	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		imageTexture,
		&renderQuad,
		&canvasQuad
	);

	//DEBUG("Current drawing: " << mCurrentSprite);
	//DEBUG("Updating frame.");
	updateFrameBasedOntime();

}

void Animation::updateQuad(){
	// DEBUG("Updating render quad.")
	// DEBUG("Something is wrong here.");
	// DEBUG("mCurrentSprite: " << mCurrentSprite);
	// DEBUG("mSpriteList[mCurrentSprite]->spriteX" << mSpriteList[mCurrentSprite]->spriteX);
	renderQuad = {
		mSpriteList[mCurrentSprite]->spriteX,
		mSpriteList[mCurrentSprite]->spriteY,
		mSpriteList[mCurrentSprite]->spriteWidth,
		mSpriteList[mCurrentSprite]->spriteHeight
	};

	//DEBUG("Updating canvas quad.");
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		(int)(mSpriteList[mCurrentSprite]->spriteWidth * zoomFactor),
		(int)(mSpriteList[mCurrentSprite]->spriteHeight * zoomFactor),
	};
}

void Animation::checkLimits(){
	if(mCurrentSprite > mEndFrame){
		if(mLoop){
			mCurrentSprite = 0;
			mCurrentAnimationTime = 0.0f;
			mState = AnimationState::STOPPED;
		}else{
			mCurrentSprite = mEndFrame;
			mState = AnimationState::FINISHED;
		}
	}
}

void Animation::updateFrameBasedOntime(){
	mCurrentAnimationTime += Game::instance.GetTimer().GetDeltaTime();
	mCurrentSprite = mCurrentAnimationTime / mEachFrameTime + mStartFrame;
}

void Animation::updateGameObjectMeasures(){
	gameObject->mHalfSize.first = mSpriteList[mCurrentSprite]->spriteWidth * zoomFactor / 2.0f;
	gameObject->mHalfSize.second = mSpriteList[mCurrentSprite]->spriteHeight * zoomFactor / 2.0f;
	gameObject->mCenter.first = gameObject->mCurrentPosition.first + gameObject->mHalfSize.first;
	gameObject->mCenter.second = gameObject->mCurrentPosition.second + gameObject->mHalfSize.second;
}

void Animation::disableComponent(){
	this->componentState = State::DISABLED;
	mCurrentAnimationTime = 0.0f;
	mCurrentSprite = mStartFrame;
}
