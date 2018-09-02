#include "obstacle.hpp"

using namespace Azo;

obstacle::obstacle(){}

obstacle::~obstacle(){}

void obstacle::shutDown(){
	for(auto eachBlock : mBlockList){
		if(eachBlock != NULL){
			eachBlock->shutDown();
			delete(eachBlock);
			eachBlock = NULL;
		}
	}

	if(mTurningAnimationSprites.size() > 0){
		for(auto eachAnimation : mTurningAnimationSprites){
			if(eachAnimation != NULL){
				delete(eachAnimation);
				eachAnimation = NULL;
			}
		}
	}

	if(mobstacleImage != NULL){
		delete(mobstacleImage);
		mobstacleImage = NULL;
	}

	if(mAudioController != NULL){
		mAudioController->shutDown();
		delete(mAudioController);
		mAudioController = NULL;
	}

	if(mCollected != NULL){
		mCollected = NULL;
	}

	if(mTurning != NULL){
		delete(mTurning);
		mTurning = NULL;
	}


	if(mMachinePartCode != NULL){
		mMachinePartCode->shutDown();
		delete(mMachinePartCode);
		mMachinePartCode = NULL;
	}
}


obstacle::obstacle(std::string name, std::pair<double, double> positionRelativeToParent, obstacleType obstacleType){
	mName = name;
	mPositionRelativeToParent = positionRelativeToParent;
	mCurrentPosition = mPositionRelativeToParent;

	mobstacleType = obstacleType;

	createComponents();
}

// Here we add the imagens/sound to the obstacle, based on its type.
void obstacle::createComponents(){
	DEBUG("Creating obstacle components.");
	if(mobstacleType == obstacleType::WESTERN_CAR){
		DEBUG("obstacle is a WESTERN CAR!");
		mobstacleImage = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
		this->AddComponent(*mobstacleImage);
		createBlocks();

	}else if(mobstacleType == obstacleType::WESTERN_BOX){
		DEBUG("obstacle is a WESTERN BOX!");
		mobstacleImage = new engine::ImageComponent(*this, "backgrounds/box.png", 1);
		this->AddComponent(*mobstacleImage);
		createBlocks();

	}else if(mobstacleType == obstacleType::WESTERN_RAISED_BOX){
		DEBUG("obstacle is a WESTERN RAISED BOX!");
		mobstacleImage = new engine::ImageComponent(*this, "backgrounds/raised_box.png", 1);
		this->AddComponent(*mobstacleImage);
		createBlocks();

	}else if(mobstacleType == obstacleType::WESTERN_ROCK){
		DEBUG("obstacle is a WESTERN ROCK");
		mobstacleImage = new engine::ImageComponent(*this, "backgrounds/rock.png", 1);
		this->AddComponent(*mobstacleImage);
		createBlocks();

	}else if(mobstacleType == obstacleType::MACHINE_PART){
		DEBUG("obstacle is a MACHINE PART");
		mMachinePartState = MachinePartState::NON_COLLECTED;
		genTurningAnimation();
		mTurning = new engine::Animation(*this, "sprites/machinePart.png", 1200.0f, mTurningAnimationSprites, 0, 23, true, 1);
		this->AddComponent(*mTurning);

		mAudioController = new engine::AudioController();
		mCollected = new engine::AudioComponent(*this, "audios/coleta.ogg", false, false);
		mAudioController->AddAudio("coleta", *mCollected);
		this->AddComponent(*mAudioController);

		mMachinePartCode = new machinePartCode(this);
		this->AddComponent(*mMachinePartCode);

	}else if(mobstacleType == obstacleType::WESTERN_SPIKE){
		DEBUG("obstacle is a WESTERN SPIKE");

		mobstacleImage = new engine::ImageComponent(*this, "backgrounds/Espinhos_rose.png", 1);
		this->AddComponent(*mobstacleImage);
		createBlocks();
	}else if(mobstacleType == obstacleType::WESTERN_POST){
		DEBUG("obstacle is a WESTERN POST");

		mobstacleImage = new engine::ImageComponent(*this, "backgrounds/obstaculoDescer2.png", 1);
		this->AddComponent(*mobstacleImage);
		createBlocks();
	}else if(mobstacleType == obstacleType::GROUND){
		createBlocks();
	}
}

// Here we create the invisible objects that make the obstacle.
// The name attribute of the InvisibleBlock isn't needed. It's for testing only.
// It's important to create the blocks based on the type of the object.
void obstacle::createBlocks(){

	// We initialize the block' position as the position relative to parent of the obstacle.
	// This way we can position things inside the obstacle just by adding values.
	std::pair<double, double> blockPosition = mPositionRelativeToParent;

	//setting obstacle position based on its type

	if(mobstacleType == obstacleType::GROUND){
		//	DEBUG("Creating invisible block for the ground.");
		mBlockList.push_back(new InvisibleBlock("block_1", blockPosition, std::make_pair(21000, 100))); //obstacle size
		//	DEBUG("List size: " << mBlockList.size());
	}else if(mobstacleType == obstacleType::WESTERN_CAR){

		blockPosition.first += 69;
		blockPosition.second += 20;

		mBlockList.push_back(new InvisibleBlock("block_2", blockPosition, std::make_pair(109, 143)));
	}else if(mobstacleType == obstacleType::WESTERN_BOX){
		blockPosition.first += 58;
		blockPosition.second += 6;

		mBlockList.push_back(new InvisibleBlock("block_3", blockPosition, std::make_pair(63, 73)));
	}else if(mobstacleType == obstacleType::WESTERN_RAISED_BOX){
		blockPosition.first += 35;
		blockPosition.second += 6;

		mBlockList.push_back(new InvisibleBlock("block_4", blockPosition, std::make_pair(50, 68)));
	}else if(mobstacleType == obstacleType::WESTERN_ROCK){
		blockPosition.first += 80;
		blockPosition.second += 12;

		mBlockList.push_back(new InvisibleBlock("block_5", blockPosition, std::make_pair(4, 100)));
	}else if(mobstacleType == obstacleType::WESTERN_SPIKE){
		blockPosition.first += 19;
		blockPosition.second += 23;

		mBlockList.push_back(new InvisibleBlock("block_6", blockPosition, std::make_pair(210, 92)));
	}else if(mobstacleType == obstacleType::WESTERN_POST){
		blockPosition.first += 48;
		blockPosition.second += 32;

		mBlockList.push_back(new InvisibleBlock("block_7", blockPosition, std::make_pair(23, 106)));
	}

}

void obstacle::genTurningAnimation(){
	for(int i = 0; i < 24; i++){
		mTurningAnimationSprites.push_back(new engine::Sprite());
	}

	/*
    Set the animation sprite coordinates (x, y)
    and its Width and Height based on its coordinates (width - spriteX) and (Height - spriteY)
  */

	mTurningAnimationSprites[0]->sprite_x = 13;
	mTurningAnimationSprites[0]->sprite_y = 11;
	mTurningAnimationSprites[0]->sprite_width = 49 - 13;
	mTurningAnimationSprites[0]->sprite_height = 47 - 11;

	mTurningAnimationSprites[1]->sprite_x = 50;
	mTurningAnimationSprites[1]->sprite_y = 11;
	mTurningAnimationSprites[1]->sprite_width = 86 - 50;
	mTurningAnimationSprites[1]->sprite_height = 47 - 11;

	mTurningAnimationSprites[2]->sprite_x = 87;
	mTurningAnimationSprites[2]->sprite_y = 11;
	mTurningAnimationSprites[2]->sprite_width = 123 - 87;
	mTurningAnimationSprites[2]->sprite_height = 47 - 11;

	mTurningAnimationSprites[3]->sprite_x = 124;
	mTurningAnimationSprites[3]->sprite_y = 11;
	mTurningAnimationSprites[3]->sprite_width = 160 - 124;
	mTurningAnimationSprites[3]->sprite_height = 47 - 11;

	mTurningAnimationSprites[4]->sprite_x = 161;
	mTurningAnimationSprites[4]->sprite_y = 11;
	mTurningAnimationSprites[4]->sprite_width = 197 - 161;
	mTurningAnimationSprites[4]->sprite_height = 47 - 11;

	mTurningAnimationSprites[5]->sprite_x = 198;
	mTurningAnimationSprites[5]->sprite_y = 11;
	mTurningAnimationSprites[5]->sprite_width = 234 - 198;
	mTurningAnimationSprites[5]->sprite_height = 47 - 11;

	mTurningAnimationSprites[6]->sprite_x = 240;
	mTurningAnimationSprites[6]->sprite_y = 11;
	mTurningAnimationSprites[6]->sprite_width = 271 - 240;
	mTurningAnimationSprites[6]->sprite_height = 47 - 11;

	mTurningAnimationSprites[7]->sprite_x = 277;
	mTurningAnimationSprites[7]->sprite_y = 11;
	mTurningAnimationSprites[7]->sprite_width = 308 - 277;
	mTurningAnimationSprites[7]->sprite_height = 47 - 11;

	mTurningAnimationSprites[8]->sprite_x = 314;
	mTurningAnimationSprites[8]->sprite_y = 11;
	mTurningAnimationSprites[8]->sprite_width = 345 - 314;
	mTurningAnimationSprites[8]->sprite_height = 47 - 11;

	mTurningAnimationSprites[9]->sprite_x = 351;
	mTurningAnimationSprites[9]->sprite_y = 11;
	mTurningAnimationSprites[9]->sprite_width = 382 - 351;
	mTurningAnimationSprites[9]->sprite_height = 47 - 11;

	mTurningAnimationSprites[10]->sprite_x = 388;
	mTurningAnimationSprites[10]->sprite_y = 11;
	mTurningAnimationSprites[10]->sprite_width = 419 - 388;
	mTurningAnimationSprites[10]->sprite_height = 47 - 11;

	mTurningAnimationSprites[11]->sprite_x = 425;
	mTurningAnimationSprites[11]->sprite_y = 11;
	mTurningAnimationSprites[11]->sprite_width = 456 - 425;
	mTurningAnimationSprites[11]->sprite_height = 47 - 11;

	mTurningAnimationSprites[12]->sprite_x = 461;
	mTurningAnimationSprites[12]->sprite_y = 11;
	mTurningAnimationSprites[12]->sprite_width = 497 - 461;
	mTurningAnimationSprites[12]->sprite_height = 47 - 11;

	mTurningAnimationSprites[13]->sprite_x = 461;
	mTurningAnimationSprites[13]->sprite_y = 11;
	mTurningAnimationSprites[13]->sprite_width = 497 - 461;
	mTurningAnimationSprites[13]->sprite_height = 47 - 11;

	mTurningAnimationSprites[14]->sprite_x = 461;
	mTurningAnimationSprites[14]->sprite_y = 11;
	mTurningAnimationSprites[14]->sprite_width = 497 - 461;
	mTurningAnimationSprites[14]->sprite_height = 47 - 11;

	mTurningAnimationSprites[15]->sprite_x = 461;
	mTurningAnimationSprites[15]->sprite_y = 11;
	mTurningAnimationSprites[15]->sprite_width = 497 - 461;
	mTurningAnimationSprites[15]->sprite_height = 47 - 11;

	mTurningAnimationSprites[16]->sprite_x = 461;
	mTurningAnimationSprites[16]->sprite_y = 11;
	mTurningAnimationSprites[16]->sprite_width = 497 - 461;
	mTurningAnimationSprites[16]->sprite_height = 47 - 11;

	mTurningAnimationSprites[17]->sprite_x = 461;
	mTurningAnimationSprites[17]->sprite_y = 11;
	mTurningAnimationSprites[17]->sprite_width = 497 - 461;
	mTurningAnimationSprites[17]->sprite_height = 47 - 11;

	mTurningAnimationSprites[18]->sprite_x = 689;
	mTurningAnimationSprites[18]->sprite_y = 11;
	mTurningAnimationSprites[18]->sprite_width = 720 - 689;
	mTurningAnimationSprites[18]->sprite_height = 47 - 11;

	mTurningAnimationSprites[19]->sprite_x = 726;
	mTurningAnimationSprites[19]->sprite_y = 11;
	mTurningAnimationSprites[19]->sprite_width = 757 - 726;
	mTurningAnimationSprites[19]->sprite_height = 47 - 11;

	mTurningAnimationSprites[20]->sprite_x = 763;
	mTurningAnimationSprites[20]->sprite_y = 11;
	mTurningAnimationSprites[20]->sprite_width = 794 - 763;
	mTurningAnimationSprites[20]->sprite_height = 47 - 11;

	mTurningAnimationSprites[21]->sprite_x = 800;
	mTurningAnimationSprites[21]->sprite_y = 11;
	mTurningAnimationSprites[21]->sprite_width = 831 - 800;
	mTurningAnimationSprites[21]->sprite_height = 47 - 11;

	mTurningAnimationSprites[22]->sprite_x = 837;
	mTurningAnimationSprites[22]->sprite_y = 11;
	mTurningAnimationSprites[22]->sprite_width = 868 - 837;
	mTurningAnimationSprites[22]->sprite_height = 47 - 11;

	mTurningAnimationSprites[23]->sprite_x = 874;
	mTurningAnimationSprites[23]->sprite_y = 11;
	mTurningAnimationSprites[23]->sprite_width = 905 - 874;
	mTurningAnimationSprites[23]->sprite_height = 47 - 11;

}
