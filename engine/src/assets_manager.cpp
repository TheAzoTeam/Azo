#include "assets_manager.hpp"
#include "game.hpp"

using namespace engine;

AssetsManager::AssetsManager(){}


// Load image into image map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Image* AssetsManager::LoadImage(std::string image_path){
	DEBUG("Trying to load image " << image_path);
	//DEBUG("Image Map size before loading " << image_map.size());

	if(image_map.find(image_path) == image_map.end()){
		INFO("Loading a new image asset.");

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
			ERROR("Couldn't create texture from image: " << SDL_GetError());
		}

		InsertIntoImageMap(image_path, image, image_texture);

		SDL_FreeSurface(image);

	}else{
		// Nothing to do.
		DEBUG("Image: " << image_path << " already loaded!");
	}

	return image_map[image_path];
}

// Create a new Struct Image variable, which whom we will add to the map.
void AssetsManager::InsertIntoImageMap(std::string image_path, SDL_Surface* image, SDL_Texture *image_texture){
	ASSERT(image_path != "", "Image path can't be empty.");
	ASSERT(image != NULL, "SDL_Suface pointer can't be null.");

	Image *assets_manager_image = new Image;

	assets_manager_image->texture = image_texture;
	assets_manager_image->width = image->w;
	assets_manager_image->height = image->h;

	// Insert image into image map.
	image_map[image_path] = assets_manager_image;
	DEBUG("Image Map size after inserting " << image_map.size());
}

// Load music into music map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Mix_Music* AssetsManager::LoadMusic(std::string audioPath){
	DEBUG("Trying to load music " << audioPath);
	DEBUG("Music Map size before loading " << music_map.size());

	if(music_map.find(audioPath) == music_map.end()){
		INFO("Loading a new music asset.");

		Mix_Music * music = Mix_LoadMUS(audioPath.c_str());

		if(music == NULL){
			ERROR("Could not load music from path " << audioPath);
		}

		InsertIntoMusicMap(audioPath, music);

	}else{
		// Nothing to do.
		DEBUG("Music: " << audioPath << " already loaded!");
	}

	return music_map[audioPath];
}

// We will add a music to map.
void AssetsManager::InsertIntoMusicMap(std::string audioPath, Mix_Music * music){
	ASSERT(audioPath != "", "Music path can't be empty.");
	ASSERT(music != NULL, "Mix_Music pointer can't be null.");

	// Insert music into image map.
	music_map[audioPath] = music;
	DEBUG("Music Map size after inserting " << music_map.size());
}


// Load sound into sound map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Mix_Chunk* AssetsManager::LoadSound(std::string audioPath){
	DEBUG("Trying to load Sound " << audioPath);
	DEBUG("Sound Map size before loading " << sound_map.size());

	if(sound_map.find(audioPath) == sound_map.end()){
		INFO("Loading a new sound asset.");

		Mix_Chunk * sound = Mix_LoadWAV(audioPath.c_str());

		if(sound == NULL){
			ERROR("Could not load sound from path " << audioPath);
		}

		InsertIntoSoundMap(audioPath, sound);

	}else{
		// Nothing to do.
		DEBUG("Sound: " << audioPath << " already loaded!");
	}

	return sound_map[audioPath];
}

// We will add a sound to map.
void AssetsManager::InsertIntoSoundMap(std::string audioPath, Mix_Chunk * sound){
	ASSERT(audioPath != "", "Sound path can't be empty.");
	ASSERT(sound != NULL, "Mix_Chunk pointer can't be null.");

	// Insert sound into image map.
	sound_map[audioPath] = sound;
	DEBUG("Sound Map size after inserting " << sound_map.size());
}
