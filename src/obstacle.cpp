/**
 * @file obstacle.cpp
 * @brief Purpose: Contains the Obstacle class methods.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "obstacle.hpp"

using namespace Azo;

/**
 * @brief Basic contructor for Obstacle.
 *
 * Default basic constructor for Obstacle.
 */
Obstacle::Obstacle() {}

/**
 * @brief Virtual constructor for Obstacle.
 *
 * Default virtual constructor for Obstacle.
 */
Obstacle::~Obstacle(){}


/**
 * @brief Destructor class for Obstacle.
 *
 * Used for shutting down each one of the Obstacle's attributes so as to free
 * memory when closing the game.
 */
void Obstacle::shutdown() {
	// Each block in mBlockList must be shutdown before Obstacle can also be shut down.
	for (auto eachBlock : mBlockList) {
		if (eachBlock != NULL) {
			eachBlock->shutdown();
			delete(eachBlock);
			eachBlock = NULL;
		} else {
			//Nothing to do, the pointer is already null
		}
	}

	// Clear any animations remaining before shutdding down Obstacle.
	if (mTurningAnimationSprites.size() > 0) {
		for (auto eachAnimation : mTurningAnimationSprites) {
			if (eachAnimation != NULL) {
				delete(eachAnimation);
				eachAnimation = NULL;
			} else {
				//Nothing to do, the pointer is already null
			}
		}
	} else {
		//Nothing to do, there is no mTurningAnimationSprites
	}

	// Clear all remaining images.
	if (mObstacleImage != NULL) {
		delete(mObstacleImage);
		mObstacleImage = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}

	// Clear all remaining audio.
	if (mAudioController != NULL) {
		mAudioController->shutdown();
		delete(mAudioController);
		mAudioController = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}

	// Reset mCollected value.
	if (mCollected != NULL) {
		mCollected = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}

	// Reset mTurning value.
	if (mTurning != NULL) {
		delete(mTurning);
		mTurning = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}

	// Shutdown mMachinePart code.
	if (mMachinePartCode != NULL) {
		mMachinePartCode->shutdown();
		delete(mMachinePartCode);
		mMachinePartCode = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}
}


/**
 * @brief Constructor class for Obstacle.
 *
 * Used to initialize Obstacle class variables.
 * @param name Obstacle name.
 * @param positionRelativeToParent Pair of doubles relative to position(range > 0).
 * @param obstacleType Type of obstacle according to enum class ObstacleType from obstacle.hpp .
 */
Obstacle::Obstacle(std::string name, std::pair<double, double> positionRelativeToParent, ObstacleType obstacleType) {
	// Initializing Obstacle variables.
	mName = name;
	ASSERT(mName != "", "name can't be empty.");
	mPositionRelativeToParent = positionRelativeToParent;
	mCurrentPosition = mPositionRelativeToParent;
	mObstacleType = obstacleType;

	createComponents();
}


/**
 * @brief Method for creating components to Obstacle.
 *
 * Used for creating components according to its type (AudioComponent or ImageComponent).
 */
void Obstacle::createComponents() {
	DEBUG("Creating obstacle components.");
	// If and else if blocks for each ObstacleType and its respective initialization.
	switch (mObstacleType) {
		case ObstacleType::WESTERN_CAR:
			DEBUG("obstacle is a WESTERN CAR!");
			mObstacleImage = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
			ASSERT(mObstacleImage != NULL, "ObstacleType::WESTERN_CAR, mObstacleImage can't be NULL.");
			this->addComponent(*mObstacleImage);
			createBlocks();
			break;

		case ObstacleType::WESTERN_BOX:
			DEBUG("obstacle is a WESTERN BOX!");
			mObstacleImage = new engine::ImageComponent(*this, "backgrounds/box.png", 1);
			ASSERT(mObstacleImage != NULL, "ObstacleType::WESTERN_BOX, mObstacleImage can't be NULL.");
			this->addComponent(*mObstacleImage);
			createBlocks();
			break;

		case ObstacleType::WESTERN_RAISED_BOX:
			DEBUG("obstacle is a WESTERN RAISED BOX!");
			mObstacleImage = new engine::ImageComponent(*this, "backgrounds/raised_box.png", 1);
			ASSERT(mObstacleImage != NULL, "ObstacleType::WESTERN_RAISED_BOX, mObstacleImage can't be NULL.");
			this->addComponent(*mObstacleImage);
			createBlocks();
			break;

		case ObstacleType::WESTERN_ROCK:
			DEBUG("obstacle is a WESTERN ROCK");
			mObstacleImage = new engine::ImageComponent(*this, "backgrounds/rock.png", 1);
			ASSERT(mObstacleImage != NULL, "ObstacleType::WESTERN_ROCK, mObstacleImage can't be NULL.");
			this->addComponent(*mObstacleImage);
			createBlocks();
			break;

		case ObstacleType::MACHINE_PART:
			DEBUG("obstacle is a MACHINE PART");
			mMachinePartState = MachinePartState::NON_COLLECTED;
			generateTurningAnimation();
			mTurning = new engine::Animation(*this, "sprites/machine_part.png", 1200.0f, mTurningAnimationSprites, 0, 23, true, 1);
			this->addComponent(*mTurning);

			mAudioController = new engine::AudioController();
			ASSERT(mAudioController != NULL, "engine::AudioController, AudioController can't be NULL.");
			mCollected = new engine::AudioComponent(*this, "audios/coleta.ogg", false, false);
			ASSERT(mCollected != NULL, "engine::AudioComponent, AudioComponent can't be NULL.");
			mAudioController->addAudio("coleta", *mCollected);
			this->addComponent(*mAudioController);

			mMachinePartCode = new MachinePartCode(this);
			ASSERT(mMachinePartCode != NULL, "MachinePartCode, mMachinePartCode can't return NULL.");
			this->addComponent(*mMachinePartCode);
			break;

		case ObstacleType::WESTERN_SPIKE:
			DEBUG("obstacle is a WESTERN SPIKE");
			mObstacleImage = new engine::ImageComponent(*this, "backgrounds/Espinhos_rose.png", 1);
			ASSERT(mObstacleImage != NULL, "engine::ImageComponent, mObstacleImage can't be NULL.");
			this->addComponent(*mObstacleImage);
			createBlocks();
			break;

		case ObstacleType::WESTERN_POST:
			DEBUG("obstacle is a WESTERN POST");
			mObstacleImage = new engine::ImageComponent(*this, "backgrounds/obstaculoDescer2.png", 1);
			ASSERT(mObstacleImage != NULL, "engine::ImageComponent, mObstacleImage can't be NULL.");
			this->addComponent(*mObstacleImage);
			createBlocks();
			break;
		
		case ObstacleType::GROUND:
			createBlocks();
			break;

		default:
			//Nothing to do, there is no component with this type
			break;
	}
}


/**
 * @brief Method for creating blocks.
 *
 * Used to create invisible objects that compose the Obstacle based on the type
 * of the object.
 * Note that the name of the InvisibleBlock is only for internal use.
 */
void Obstacle::createBlocks() {

	/*
	  We initialize the block' position as the position relative to parent of the obstacle.
	  This way we can position things inside the obstacle just by adding values to the position.
	*/
	std::pair<double, double> blockPosition = mPositionRelativeToParent;

	// If and else if blocks for setting obstacle position based on its type ObstacleType.
	if (mObstacleType == ObstacleType::GROUND) {
		mBlockList.push_back(new InvisibleBlock("block_1", blockPosition, std::make_pair(21000, 100)));
	} else if (mObstacleType == ObstacleType::WESTERN_CAR) {

		blockPosition.first += 69;
		blockPosition.second += 20;

		mBlockList.push_back(new InvisibleBlock("block_2", blockPosition, std::make_pair(109, 143)));
	} else if (mObstacleType == ObstacleType::WESTERN_BOX) {
		blockPosition.first += 58;
		blockPosition.second += 6;

		mBlockList.push_back(new InvisibleBlock("block_3", blockPosition, std::make_pair(63, 73)));
	} else if (mObstacleType == ObstacleType::WESTERN_RAISED_BOX) {
		blockPosition.first += 35;
		blockPosition.second += 6;

		mBlockList.push_back(new InvisibleBlock("block_4", blockPosition, std::make_pair(50, 68)));
	} else if (mObstacleType == ObstacleType::WESTERN_ROCK) {
		blockPosition.first += 80;
		blockPosition.second += 12;

		mBlockList.push_back(new InvisibleBlock("block_5", blockPosition, std::make_pair(4, 100)));
	} else if (mObstacleType == ObstacleType::WESTERN_SPIKE) {
		blockPosition.first += 19;
		blockPosition.second += 23;

		mBlockList.push_back(new InvisibleBlock("block_6", blockPosition, std::make_pair(210, 92)));
	} else if (mObstacleType == ObstacleType::WESTERN_POST) {
		blockPosition.first += 48;
		blockPosition.second += 32;

		mBlockList.push_back(new InvisibleBlock("block_7", blockPosition, std::make_pair(23, 106)));
	}

}


/**
 * @brief Method for setting up animated obstacles.
 *
 * Used for generating animations for obstacles that have animated sprites.
 */
void Obstacle::generateTurningAnimation() {
	// Default animation speed is 24 frames per second.
	const int NUMBER_SPRITES_TURNING_ANIMATION = 24;
	// Fill sprites animation up to the NUMBER_SPRITES_TURNING_ANIMATION const.
	for (int i = 0; i < NUMBER_SPRITES_TURNING_ANIMATION; i++) {
		mTurningAnimationSprites.push_back(new engine::Sprite());
	}

	/*
      Set the animation sprite coordinates (x, y)
      and its Width and Height based on its coordinates (width - spriteX) and (Height - spriteY).
  	*/

	mTurningAnimationSprites[0]->spriteX = 13;
	mTurningAnimationSprites[0]->spriteY = 11;
	mTurningAnimationSprites[0]->spriteWidth = 49 - 13;
	mTurningAnimationSprites[0]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[1]->spriteX = 50;
	mTurningAnimationSprites[1]->spriteY = 11;
	mTurningAnimationSprites[1]->spriteWidth = 86 - 50;
	mTurningAnimationSprites[1]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[2]->spriteX = 87;
	mTurningAnimationSprites[2]->spriteY = 11;
	mTurningAnimationSprites[2]->spriteWidth = 123 - 87;
	mTurningAnimationSprites[2]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[3]->spriteX = 124;
	mTurningAnimationSprites[3]->spriteY = 11;
	mTurningAnimationSprites[3]->spriteWidth = 160 - 124;
	mTurningAnimationSprites[3]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[4]->spriteX = 161;
	mTurningAnimationSprites[4]->spriteY = 11;
	mTurningAnimationSprites[4]->spriteWidth = 197 - 161;
	mTurningAnimationSprites[4]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[5]->spriteX = 198;
	mTurningAnimationSprites[5]->spriteY = 11;
	mTurningAnimationSprites[5]->spriteWidth = 234 - 198;
	mTurningAnimationSprites[5]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[6]->spriteX = 240;
	mTurningAnimationSprites[6]->spriteY = 11;
	mTurningAnimationSprites[6]->spriteWidth = 271 - 240;
	mTurningAnimationSprites[6]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[7]->spriteX = 277;
	mTurningAnimationSprites[7]->spriteY = 11;
	mTurningAnimationSprites[7]->spriteWidth = 308 - 277;
	mTurningAnimationSprites[7]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[8]->spriteX = 314;
	mTurningAnimationSprites[8]->spriteY = 11;
	mTurningAnimationSprites[8]->spriteWidth = 345 - 314;
	mTurningAnimationSprites[8]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[9]->spriteX = 351;
	mTurningAnimationSprites[9]->spriteY = 11;
	mTurningAnimationSprites[9]->spriteWidth = 382 - 351;
	mTurningAnimationSprites[9]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[10]->spriteX = 388;
	mTurningAnimationSprites[10]->spriteY = 11;
	mTurningAnimationSprites[10]->spriteWidth = 419 - 388;
	mTurningAnimationSprites[10]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[11]->spriteX = 425;
	mTurningAnimationSprites[11]->spriteY = 11;
	mTurningAnimationSprites[11]->spriteWidth = 456 - 425;
	mTurningAnimationSprites[11]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[12]->spriteX = 461;
	mTurningAnimationSprites[12]->spriteY = 11;
	mTurningAnimationSprites[12]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[12]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[13]->spriteX = 461;
	mTurningAnimationSprites[13]->spriteY = 11;
	mTurningAnimationSprites[13]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[13]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[14]->spriteX = 461;
	mTurningAnimationSprites[14]->spriteY = 11;
	mTurningAnimationSprites[14]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[14]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[15]->spriteX = 461;
	mTurningAnimationSprites[15]->spriteY = 11;
	mTurningAnimationSprites[15]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[15]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[16]->spriteX = 461;
	mTurningAnimationSprites[16]->spriteY = 11;
	mTurningAnimationSprites[16]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[16]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[17]->spriteX = 461;
	mTurningAnimationSprites[17]->spriteY = 11;
	mTurningAnimationSprites[17]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[17]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[18]->spriteX = 689;
	mTurningAnimationSprites[18]->spriteY = 11;
	mTurningAnimationSprites[18]->spriteWidth = 720 - 689;
	mTurningAnimationSprites[18]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[19]->spriteX = 726;
	mTurningAnimationSprites[19]->spriteY = 11;
	mTurningAnimationSprites[19]->spriteWidth = 757 - 726;
	mTurningAnimationSprites[19]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[20]->spriteX = 763;
	mTurningAnimationSprites[20]->spriteY = 11;
	mTurningAnimationSprites[20]->spriteWidth = 794 - 763;
	mTurningAnimationSprites[20]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[21]->spriteX = 800;
	mTurningAnimationSprites[21]->spriteY = 11;
	mTurningAnimationSprites[21]->spriteWidth = 831 - 800;
	mTurningAnimationSprites[21]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[22]->spriteX = 837;
	mTurningAnimationSprites[22]->spriteY = 11;
	mTurningAnimationSprites[22]->spriteWidth = 868 - 837;
	mTurningAnimationSprites[22]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[23]->spriteX = 874;
	mTurningAnimationSprites[23]->spriteY = 11;
	mTurningAnimationSprites[23]->spriteWidth = 905 - 874;
	mTurningAnimationSprites[23]->spriteHeight = 47 - 11;

}
