/**
 * @file sprite.cpp
 * @brief Purpose: Controls sprites of the game.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 * 
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 * 
 * This file implements the main game component its declaration and state.
*/
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
