#include "assets_manager.hpp"
#include "game.hpp"

using namespace engine;

AssetsManager::AssetsManager(){}


// Load image into image map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Image* AssetsManager::LoadImage(std::string imagePath) {
	DEBUG("Trying to load image " << imagePath);
	//DEBUG("Image Map size before loading " << imageMap.size());

	if (imageMap.find(imagePath) == imageMap.end()) {
		INFO("Loading a new image asset.");

		SDL_Surface *image = NULL;

		if (imagePath == "") {
			ERROR("Invalid Image Path: " << imagePath);
		}

		image = IMG_Load(imagePath.c_str());

		if (image == NULL) {
			ERROR("Couldn't load sprite.");
		}

		SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(Game::instance.sdlElements.getCanvas(), image);

		if (imageTexture == NULL) {
			ERROR("Couldn't create texture from image: " << SDL_GetError());
		}

		InsertIntoImageMap(imagePath, image, imageTexture);

		SDL_FreeSurface(image);

	} else {
		// Nothing to do.
		DEBUG("Image: " << imagePath << " already loaded!");
	}

	return imageMap[imagePath];
}

// Create a new Struct Image variable, which whom we will add to the map.
void AssetsManager::InsertIntoImageMap(std::string imagePath, SDL_Surface* image, SDL_Texture *imageTexture) {
	ASSERT(imagePath != "", "Image path can't be empty.");
	ASSERT(image != NULL, "SDL_Suface pointer can't be null.");

	Image *assetsManagerImage = new Image;

	assetsManagerImage->texture = imageTexture;
	assetsManagerImage->width = image->w;
	assetsManagerImage->height = image->h;

	// Insert image into image map.
	imageMap[imagePath] = assetsManagerImage;
	DEBUG("Image Map size after inserting " << imageMap.size());
}

// Load music into music map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Mix_Music* AssetsManager::LoadMusic(std::string audioPath) {
	DEBUG("Trying to load music " << audioPath);
	DEBUG("Music Map size before loading " << musicMap.size());

	if (musicMap.find(audioPath) == musicMap.end()){
		INFO("Loading a new music asset.");

		Mix_Music * music = Mix_LoadMUS(audioPath.c_str());

		if(music == NULL) {
			ERROR("Could not load music from path " << audioPath);
		}

		InsertIntoMusicMap(audioPath, music);

	} else {
		// Nothing to do.
		DEBUG("Music: " << audioPath << " already loaded!");
	}

	return musicMap[audioPath];
}

// We will add a music to map.
void AssetsManager::InsertIntoMusicMap(std::string audioPath, Mix_Music * music) {
	ASSERT(audioPath != "", "Music path can't be empty.");
	ASSERT(music != NULL, "Mix_Music pointer can't be null.");

	// Insert music into image map.
	musicMap[audioPath] = music;
	DEBUG("Music Map size after inserting " << musicMap.size());
}


// Load sound into sound map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Mix_Chunk* AssetsManager::LoadSound(std::string audioPath) {
	DEBUG("Trying to load Sound " << audioPath);
	DEBUG("Sound Map size before loading " << soundMap.size());

	if (soundMap.find(audioPath) == soundMap.end()) {
		INFO("Loading a new sound asset.");

		Mix_Chunk * sound = Mix_LoadWAV(audioPath.c_str());

		if (sound == NULL) {
			ERROR("Could not load sound from path " << audioPath);
		}

		InsertIntoSoundMap(audioPath, sound);

	} else {
		// Nothing to do.
		DEBUG("Sound: " << audioPath << " already loaded!");
	}

	return soundMap[audioPath];
}

// We will add a sound to map.
void AssetsManager::InsertIntoSoundMap(std::string audioPath, Mix_Chunk * sound) {
	ASSERT(audioPath != "", "Sound path can't be empty.");
	ASSERT(sound != NULL, "Mix_Chunk pointer can't be null.");

	// Insert sound into image map.
	soundMap[audioPath] = sound;
	DEBUG("Sound Map size after inserting " << soundMap.size());
}
