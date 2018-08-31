#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <iostream>
#include <unordered_map>

#include "sdl2include.h"
#include "log.h"

namespace engine {

	// Struct used to map width and height from a image or a sprite.
	// We also map the texture, which whom we will draw in canvas.
	struct Image {
		SDL_Texture * texture;
		unsigned int width;
		unsigned int height;
	};

	class AssetsManager {
		private:
			std::unordered_map<std::string, Image *> imageMap;     // Map of all images already loaded.
			std::unordered_map<std::string, Mix_Music *> musicMap; // Map of all musics already loaded.
			std::unordered_map<std::string, Mix_Chunk *> soundMap; // Map of all sounds already loaded.
		public:
			AssetsManager();

			Image* LoadImage(std::string imagePath);

			Mix_Music* LoadMusic(std::string audioPath);

			Mix_Chunk * LoadSound(std::string audioPath);

			//TODO(Roger) Create method to shutdown all imagens in map, and put that method in the
			//scene shutdown.
		private:
			void InsertIntoImageMap(std::string imagePath, SDL_Surface* image, SDL_Texture *imageTexture);
			void InsertIntoMusicMap(std::string audioPath, Mix_Music * music);
			void InsertIntoSoundMap(std::string audioPath, Mix_Chunk * sound);
	};
}

#endif
