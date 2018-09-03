#include "image_component.hpp"
#include "game.hpp"

using namespace engine;

ImageComponent::ImageComponent(){}

ImageComponent::~ImageComponent(){}

ImageComponent::ImageComponent(GameObject &gameObject, std::string imagePath, double zoomFactor){
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->zoomFactor = zoomFactor;
}

ImageComponent::ImageComponent(GameObject &gameObject,
			       std::string imagePath,
			       double zoomFactor,
			       std::pair<double, double> positionRelativeToObject){
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->zoomFactor = zoomFactor;
	mPositionRelativeToObject = positionRelativeToObject;
}

void ImageComponent::init(){
	// Check AssetsManager to see if image is already loaded.
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(imagePath);

	imageTexture = assets_image->texture;

	component_width = assets_image->width * zoomFactor;
	component_height = assets_image->height * zoomFactor;

	gameObject->m_size.first = component_width;
	gameObject->m_size.second = component_height;

	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		component_width,
		component_height
	};

	renderQuad = {0, 0, component_width, component_height};

}


void ImageComponent::draw(){
	UpdateQuad();
	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		imageTexture,
		&renderQuad,
		&canvasQuad
		);
}

void ImageComponent::UpdateQuad(){
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		component_width,
		component_height
	};
}
