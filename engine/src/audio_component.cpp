#include "audio_component.hpp"
#include "game.hpp"


using namespace engine;

AudioComponent::AudioComponent(){}


AudioComponent::~AudioComponent(){}


AudioComponent::AudioComponent(GameObject & gameObject, std::string path, bool isMusic, bool playOnStart){
	this->gameObject = &gameObject;
	this->audioPath = path;
	this->isMusic = isMusic;
	this->playOnStart = playOnStart;
	this->audio_state = AudioState::STOPPED;
	this->music = nullptr;
	this->sound = nullptr;
}


void AudioComponent::init(){
	INFO("Init audio component");

	if(isMusic){
		music = Game::instance.GetAssetsManager().LoadMusic(audioPath);
		if (music == NULL){
			ERROR("Invalid Music Path (Music = NULL): " << audioPath);
		}
	}else {
		sound = Game::instance.GetAssetsManager().LoadSound(audioPath);
		if (sound == NULL){
			ERROR("Invalid Sound Path (Sound = NULL): " << audioPath);
		}
	}

}


void AudioComponent::updateCode(){
	if(playOnStart){
		play(); // Plays audio once until end
		playOnStart = false;
	}
}


void AudioComponent::shutdown(){
	INFO("Shutdown audio component");

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
		if (audio_state == AudioState::STOPPED){
			Mix_PlayMusic (music, loops);
			INFO("Play music: " << audioPath);
		} else if (audio_state == AudioState::PAUSED){
			Mix_ResumeMusic();
			INFO("Resume music: " << audioPath);
		}

	} else {
		if (audio_state == AudioState::STOPPED){
			Mix_PlayChannel(channel, sound, 0);
			INFO("Play sound: " << audioPath);
		} else if (audio_state == AudioState::PAUSED){
			Mix_Resume(channel);
			INFO("Resume sound: " << audioPath);
		}
	}

	audio_state = AudioState::PLAYING;
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

	audio_state = AudioState::STOPPED;
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

	audio_state = AudioState::PAUSED;
}
