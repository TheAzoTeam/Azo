/**
     * @file machine_part_code.cpp
     * @brief Purpose: File responsible for creating the pieces in the game.
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */

#include "machine_part_code.hpp"
#include "obstacle.hpp"

using namespace Azo;

/**
     * @brief function responsible for creating parts that will be collected by the player
     *
     * Why: So that they can be collected throughout the game by the player
	 *
	 * @param Obstacle that has the parts that need to be collected
     */
MachinePartCode::MachinePartCode(Obstacle *machinePart) {
	mMachinePart = machinePart; // Variable responsible for the creation of the pieces of the game
	findAudioController();
}

MachinePartCode::~MachinePartCode() {}


/**
     * @brief function responsible for disabling game audio
     *
     * Why: Used to release pointer referring to the game audio
     *
     * @return "void".
     */
void MachinePartCode::shutdown(){
	if (mAudioController != NULL) {
		mAudioController = NULL;
	}
}

/**
     * @brief function responsible for finding the audio driver
     *
     * Why: To allow access to the audio driver
     *
     * @return "void".
     */
void MachinePartCode::findAudioController() {
	mAudioController = (mMachinePart->getAudioController(typeid(engine::AudioController)));
}

/** 
     * @brief function responsible for updating part State on the map
     *
     * Why: For the status of the parts to be updated
     *
     * @return "void".
     */
void MachinePartCode::updateCode() {
	switch(mMachinePart->mMachinePartState) {
		case MachinePartState::COLLECTED:
			mAudioController->playAudio("coleta");

			mMachinePart->mMachinePartState = MachinePartState::FINISHED;
			break;
		case MachinePartState::FINISHED:
			mMachinePart->mObjectState = engine::ObjectState::DISABLED;
		default:
			break;
	}
}
