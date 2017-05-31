#include "audio_component.hpp"
#include "game.hpp"


using namespace engine;


AudioComponent::AudioComponent(){}

AudioComponent::AudioComponent(GameObject & game_object, std::string path, bool is_music, bool play_on_start){
	this->game_object = &game_object;
	this->audio_path = path;
	this->is_music = is_music;
	this->play_on_start = play_on_start;
	this->audio_state = AudioState::STOPPED;
	this->music = NULL;
	this->sound = NULL;
}

bool AudioComponent::Init(){
	INFO("Init audio component");

	if(is_music){
		music = Game::instance.GetAssetsManager().LoadMusic(audio_path);

		if(music == NULL){
			ERROR("Invalid Music Path (Music = NULL): " << audio_path);
		}

	}else {
		sound = Game::instance.GetAssetsManager().LoadSound(audio_path);

		if(sound == NULL){
			ERROR("Invalid Sound Path (Sound = NULL): " << audio_path);
		}
	}

	return true;
}

bool AudioComponent::UpdateCode(){
	if(play_on_start){
		Play();
		play_on_start = false;
	}
	return true;
}

bool AudioComponent::Shutdown(){
	INFO("Shutdown audio component");
	return true;
}

void AudioComponent::Play(int loops, int channel){
	INFO("AudioComponent::Play audio: " << audio_path);

	if(is_music){
		if(audio_state == AudioState::STOPPED){
			Mix_PlayMusic(music, loops);
			INFO("Play music: " << audio_path);
		}else if(audio_state == AudioState::PAUSED){
			Mix_ResumeMusic();
			INFO("Resume music: " << audio_path);
		}

	}else{
		if(audio_state == AudioState::STOPPED){
			Mix_PlayChannel(channel, sound, loops);
			INFO("Play sound: " << audio_path);
		}else if(audio_state == AudioState::PAUSED){
			Mix_Resume(channel);
			INFO("Resume sound: " << audio_path);
		}
	}

	audio_state = AudioState::PLAYING;
}

void AudioComponent::Stop(int channel){
	INFO("AudioComponent::Stop audio: " << audio_path);

	if(is_music){
		Mix_HaltMusic();
		INFO("Stop music: " << audio_path);
	} else{
		Mix_HaltChannel(channel);
		INFO("Stop sound: " << audio_path);
	}

	audio_state = AudioState::STOPPED;
}

void AudioComponent::Pause(int channel){
	INFO("AudioComponent::Pause audio: " << audio_path);

	if(is_music){
		Mix_PauseMusic();
		INFO("Pause music: " << audio_path);
	} else{
		Mix_Pause(channel);
		INFO("Pause sound: " << audio_path);
	}

	audio_state = AudioState::PAUSED;
}
