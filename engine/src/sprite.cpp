#include "sprite.hpp"

using namespace engine;

Sprite::Sprite(){}
Sprite::Sprite(int sprite_width, int sprite_height, int sprite_x, int sprite_y){
	this->sprite_width = sprite_width;
	this->sprite_height = sprite_height;
	this->sprite_x = sprite_x;
	this->sprite_y = sprite_y;
}
Sprite::~Sprite(){}