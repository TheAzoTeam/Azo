#include "audio_controller.hpp"

using namespace engine;

AudioController::~AudioController(){}

void AudioController::Init(){
	for(auto audioRow : audioMap){
		auto audio = audioRow.second;
		audio->Init();
	}
}

void AudioController::Shutdown(){
	for(auto audioRow : audioMap){
		auto audio = audioRow.second;
		audio->Shutdown();
		audio = NULL;
	}
}

void AudioController::UpdateCode(){
	for(auto audioRow : audioMap){
		auto audio = audioRow.second;
		if(audio->isEnabled()){
			audio->UpdateCode();
		}
	}
}

AudioController::AudioController(){
	this->componentState = State::ENABLED;
}

AudioController::AudioController(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

void AudioController::addAudio(std::string audioName, AudioComponent &audio){
	audioMap[audioName] = &audio;
}

void AudioController::playAudio(std::string audioName){

	auto audioToBePlayed = audioMap.find(audioName);

	if(audioToBePlayed != audioMap.end()){
		audioToBePlayed->second->play(-1, -1);

	}else{
		ERROR("This audio doesn't exist.");
	}
}

void AudioController::stopAudio(std::string audioName){
	auto audioToBePlayed = audioMap.find(audioName);

	if(audioToBePlayed != audioMap.end()){
		audioToBePlayed->second->stop(-1);
	}else{
		ERROR("Audio couldn't be found!");
	}
}

void AudioController::stopAllAudios(){
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
}


void AudioController::pauseAudio(std::string audioName){
	auto audioToBePlayed = audioMap.find(audioName);

	if(audioToBePlayed != audioMap.end()){
		audioToBePlayed->second->pause(-1);
	}else{
		ERROR("Animation couldn't be found!");
	}
}

AudioState AudioController::getAudioState(std::string audioName){
	auto audio = audioMap.find(audioName);

	if(audio == audioMap.end()){
		ERROR("Audio doesn't exist");
	}

	return audio->second->audioState;
}
