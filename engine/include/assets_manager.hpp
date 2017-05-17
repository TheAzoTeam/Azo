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
			std::unordered_map<std::string, Image *> image_map; // Map of all images already loaded.
		public:
			AssetsManager();
			Image* LoadImage(std::string image_path);
			//TODO(Roger) Create method to shutdown all imagens in map, and put that method in the
			//scene shutdown.
		private:
			void InsertIntoMap(std::string image_path, SDL_Surface* image, SDL_Texture *image_texture);

	};
}

#endif