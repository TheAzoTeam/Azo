#ifndef AUDIO_COMPONENT_HPP
#define AUDIO_COMPONENT_HPP

#include <string>

#include "sdl2include.h"
#include "component.hpp"
#include "log.h"

namespace engine {

	enum class AudioState {
		PLAYING,
		PAUSED,
		STOPPED
	};
	
	class AudioComponent : public Component {
	private:					
		std::string audioPath;  
		bool isMusic;		    
		bool playOnStart; 		

		Mix_Music * music;      
		Mix_Chunk * sound;

	public:
		AudioState audioState;  
		AudioComponent();       
		virtual ~AudioComponent();			   
		AudioComponent(GameObject &gameObject, 
					   std::string audioPath,  
					   bool isMusic, 		   
					   bool playOnStart);	   
		void init();			
		void shutdown();		
		void updateCode();      
		void play(int loops, int channel);	  
		void stop(int channel); 			  
		void pause(int channel);			  
		inline bool getIsMusic(){ return isMusic; } 
	};

}

#endif
