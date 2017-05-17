#include "assets_manager.hpp"
#include "game.hpp"

using namespace engine;

AssetsManager::AssetsManager(){}


// Load image into image map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Image* AssetsManager::LoadImage(std::string image_path){
	DEBUG("Trying to load " << image_path);
	DEBUG("Map size before loading " << image_map.size());
	if(image_map.find(image_path) == image_map.end()){
		INFO("Loading a new asset.");

		SDL_Surface *image = NULL;

		if(image_path == ""){
			ERROR("Invalid Image Path: " << image_path);
		}

		image = IMG_Load(image_path.c_str());

		if(image == NULL){
			ERROR("Couldn't load sprite.");
		}

		SDL_Texture *image_texture = SDL_CreateTextureFromSurface(Game::instance.sdl_elements.GetCanvas(), image);

		if(image_texture == NULL){
			ERROR("Couldn't create texture from image.");
		}

		InsertIntoMap(image_path, image, image_texture);

		SDL_FreeSurface(image);

	}else{
		// Nothing to do.
		DEBUG("Image: " << image_path << " already loaded!");
	}

	return image_map[image_path];
}

// Create a new Struct Image variable, which whom we will add to the map.
void AssetsManager::InsertIntoMap(std::string image_path, SDL_Surface* image, SDL_Texture *image_texture){
	ASSERT(image_path != "", "Image path can't be empty.");
	ASSERT(image != NULL, "SDL_Suface pointer can't be null.");

	Image *assets_manager_image = new Image;

	assets_manager_image->texture = image_texture;
	assets_manager_image->width = image->w;
	assets_manager_image->height = image->h;

	// Insert image into image map.
	image_map[image_path] = assets_manager_image;
	DEBUG("Map size after inserting " << image_map.size());
}

