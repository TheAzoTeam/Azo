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
	auto assetsImage = Game::instance.GetAssetsManager().LoadImage(imagePath);

	imageTexture = assetsImage->texture;

	componentWidth = assetsImage->width * zoomFactor;
	componentHeight = assetsImage->height * zoomFactor;

	gameObject->m_size.first = componentWidth;
	gameObject->m_size.second = componentHeight;

	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		componentWidth,
		componentHeight
	};

	renderQuad = {0, 0, componentWidth, componentHeight};

}


void ImageComponent::draw(){
	UpdateQuad();
	SDL_RenderCopy(
		Game::instance.sdl_elements.getCanvas(),
		imageTexture,
		&renderQuad,
		&canvasQuad
		);
}

void ImageComponent::UpdateQuad(){
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		componentWidth,
		componentHeight
	};
}
