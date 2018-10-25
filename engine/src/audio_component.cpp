#include "audio_component.hpp"
#include "game.hpp"


using namespace engine;

AudioComponent::AudioComponent(){}


AudioComponent::~AudioComponent(){}


AudioComponent::AudioComponent(GameObject &gameObject,
							   std::string audioPath,
							   bool isMusic,
							   bool playOnStart){
	this->gameObject = &gameObject;
	this->audioPath = audioPath;
	this->isMusic = isMusic;
	this->playOnStart = playOnStart;
	this->audioState = AudioState::STOPPED;
	this->music = nullptr;
	this->sound = nullptr;
}


void AudioComponent::init(){
	INFO("init audio component");

	if (isMusic){
		music = Game::instance.getAssetsManager().LoadMusic(audioPath);
		if (music == NULL){
			ERROR("Invalid Music Path (Music = NULL): " << audioPath);
		}
	}else {
		sound = Game::instance.getAssetsManager().LoadSound(audioPath);
		if (sound == NULL){
			ERROR("Invalid Sound Path (Sound = NULL): " << audioPath);
		}
	}

}


void AudioComponent::updateCode(){
	if (playOnStart){
		play (-1, -1); // Plays audio once until end
		playOnStart = false;
	}
}


void AudioComponent::shutdown(){
	INFO("shutdown audio component");

	stop(-1);
	if(music != nullptr){
		Mix_FreeMusic(music);
		music = nullptr;
	}

	if(sound != nullptr){
		//TODO(Roger): For unkown reasons, the Mix_FreeChunk doesn't work. Find out why.
		//Mix_FreeChunk(sound);
		sound = nullptr;
	}
}


void AudioComponent::play(int loops, int channel){
	INFO("AudioComponent::Play audio: " << audioPath);

	if (isMusic){
		if (audioState == AudioState::STOPPED){
			Mix_PlayMusic (music, loops);
			INFO("Play music: " << audioPath);
		} else if (audioState == AudioState::PAUSED){
			Mix_ResumeMusic();
			INFO("Resume music: " << audioPath);
		}

	} else {
		if (audioState == AudioState::STOPPED){
			Mix_PlayChannel(channel, sound, 0);
			INFO("Play sound: " << audioPath);
		} else if (audioState == AudioState::PAUSED){
			Mix_Resume(channel);
			INFO("Resume sound: " << audioPath);
		}
	}

	audioState = AudioState::PLAYING;
}


void AudioComponent::stop(int channel){
	INFO("AudioComponent::Stop audio: " << audioPath);

	if (isMusic){
		Mix_HaltMusic();
		INFO("Stop music: " << audioPath);
	} else {
		Mix_HaltChannel(channel);
		INFO("Stop sound: " << audioPath);
	}

	audioState = AudioState::STOPPED;
}


void AudioComponent::pause(int channel){
	INFO("AudioComponent::Pause audio: " << audioPath);

	if (isMusic){
		Mix_PauseMusic();
		INFO("Pause music: " << audioPath);
	} else {
		Mix_Pause(channel);
		INFO("Pause sound: " << audioPath);
	}

	audioState = AudioState::PAUSED;
}
