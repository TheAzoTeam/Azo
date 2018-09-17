#include "sprite.hpp"

using namespace engine;

Sprite::Sprite(){}
Sprite::Sprite(int spriteWidth, int spriteHeight, int spriteX, int spriteY){
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	this->spriteX = spriteX;
	this->spriteY = spriteY;
}
Sprite::~Sprite(){}
