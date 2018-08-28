#include "image_component.hpp"
#include "game.hpp"

using namespace engine;

ImageComponent::ImageComponent(){}

ImageComponent::~ImageComponent(){}

ImageComponent::ImageComponent(GameObject &gameObject, std::string image_path, double zoom_factor){
	this->gameObject = &gameObject;
	this->image_path = image_path;
	this->zoom_factor = zoom_factor;
}

ImageComponent::ImageComponent(GameObject &gameObject,
			       std::string image_path,
			       double zoom_factor,
			       std::pair<double, double> position_relative_to_object){
	this->gameObject = &gameObject;
	this->image_path = image_path;
	this->zoom_factor = zoom_factor;
	m_position_relative_to_object = position_relative_to_object;
}

void ImageComponent::Init(){
	// Check AssetsManager to see if image is already loaded.
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(image_path);

	image_texture = assets_image->texture;

	component_width = assets_image->width * zoom_factor;
	component_height = assets_image->height * zoom_factor;

	gameObject->m_size.first = component_width;
	gameObject->m_size.second = component_height;

	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + m_position_relative_to_object.first),
		(int)(gameObject->mCurrentPosition.second + m_position_relative_to_object.second),
		component_width,
		component_height
	};

	renderQuad = {0, 0, component_width, component_height};

}


void ImageComponent::Draw(){
	UpdateQuad();
	SDL_RenderCopy(
		Game::instance.sdl_elements.GetCanvas(),
		image_texture,
		&renderQuad,
		&canvasQuad
		);
}

void ImageComponent::UpdateQuad(){
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + m_position_relative_to_object.first),
		(int)(gameObject->mCurrentPosition.second + m_position_relative_to_object.second),
		component_width,
		component_height
	};
}
