#include "sdl.hpp"

using namespace engine;


SDL::SDL(){}


// Initialize all SDL attributes: Windows, Canvas, SDL_IMAGE, SDL_VIDEO, SDL_AUDIO.
void SDL::InitSDL(){
	INFO("Initializing SDL.");

	INFO("Initializing Audio and Video.");
	if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)){
		ERROR("SDL Video or SDL Audio couldn't be started.");
	}

	INFO("Initializing SDL Image.");
	int image_flags = IMG_INIT_PNG;

	if(!(IMG_Init(image_flags) & image_flags)){
		ERROR("SDL Image could't be started.");
	}

	INFO("Initializing SDL Mixer.");
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
		ERROR("SDL MIXER could't be started.");
	}
}


// Used inside "Run" method of the Game, creating the Window and Canvas.
void SDL::CreateWindow(){
	INFO("Creating Window.");
	window = SDL_CreateWindow(
		GAME_NAME.c_str(),      // Game window title.
		SDL_WINDOWPOS_CENTERED, // Window opening position x.
		SDL_WINDOWPOS_CENTERED, // Window opening position y.
		windowWidth,           // Window width.
		windowHeight,          // Window height.
		SDL_WINDOW_SHOWN
		);

	if(window == NULL){
		ERROR( "Couldn't create window.");
	}

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	INFO("Creating canvas.");
	canvas = SDL_CreateRenderer(
		window,                                                 // Window pointer
		-1,                                                     // The index to the rendering driver, or -1 to the first one
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC    // Flag. The renderer will use hardware acceleration
		);

	if(canvas == NULL){
		ERROR("Couldn't create renderer (Canvas).");
	}

	/* Set window color when redrawing */
	SDL_SetRenderDrawColor(
		canvas, // Renderer pointer
		0xff,   // (R)ed color
		0xff,   // (G)reen color
		0xff,   // (B)lue color
		0xff);  // Opacity (alpha)
}


// Used in the Main Loop's End.
void SDL::TerminateSDL(){
	INFO("Terminating SDL.");

	DEBUG("Destroying Renderer");
	SDL_DestroyRenderer(canvas);
	canvas = NULL;

	DEBUG("Destroying Window");
	SDL_DestroyWindow(window);
	window = NULL;

	DEBUG("Quitting IMG.");
	IMG_Quit();

	DEBUG("Quitting MIX");
	Mix_Quit();

	SDL_Quit();
	INFO("Bye bye, SDL.");
}


// Receive attributes of the Game instance, throught "SetGameAttributes" method.
void SDL::SetSDLAttributes(std::string GAME_NAME, int windowWidth, int windowHeight){
	this->GAME_NAME = GAME_NAME;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}
