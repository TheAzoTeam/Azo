#include "image_component.hpp"
#include "game.hpp"

using namespace engine;

ImageComponent::ImageComponent(){}

ImageComponent::~ImageComponent(){}

ImageComponent::ImageComponent(GameObject &game_object, std::string image_path, double zoom_factor){
	this->game_object = &game_object;
	this->image_path = image_path;
	this->zoom_factor = zoom_factor;
}

ImageComponent::ImageComponent(GameObject &game_object,
			       std::string image_path,
			       double zoom_factor,
			       std::pair<double, double> position_relative_to_object){
	this->game_object = &game_object;
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

	game_object->m_size.first = component_width;
	game_object->m_size.second = component_height;

	canvasQuad = {
		(int)(game_object->m_current_position.first + m_position_relative_to_object.first),
		(int)(game_object->m_current_position.second + m_position_relative_to_object.second),
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
		(int)(game_object->m_current_position.first + m_position_relative_to_object.first),
		(int)(game_object->m_current_position.second + m_position_relative_to_object.second),
		component_width,
		component_height
	};
}
