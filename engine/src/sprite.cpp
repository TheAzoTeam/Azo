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
#include "log.h"

using namespace engine;

Sprite::Sprite() {}

Sprite::Sprite(int spriteWidth, int spriteHeight, int spriteX, int spriteY) {
	ASSERT(spriteWidth > 0, "Sprite::Sprite, sprite width can't be less than zero.");
	ASSERT(spriteHeight > 0, "Sprite::Sprite, sprite height can't be less than zero.");
	ASSERT(spriteX > 0, "Sprite::Sprite, sprite x coordinate can't be less than zero.");
	ASSERT(spriteY > 0, "Sprite::Sprite, sprite y coordinate can't be less than zero.");
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	this->spriteX = spriteX;
	this->spriteY = spriteY;
}

void Sprite::setSpriteWidth(int newSpriteWidth){
	this->spriteWidth = newSpriteWidth;
}

int Sprite::getSpriteWidth(){
	return this->spriteWidth;
}

void Sprite::setSpriteHeight(int newSpriteHeight){
	this->spriteHeight = newSpriteHeight;
}

int Sprite::getSpriteHeight(){
	return this->spriteHeight;
}

void Sprite::setSpriteX(int newSpriteX){
	this->spriteX = newSpriteX;
}

int Sprite::getSpriteX(){
	return this->spriteX;
}

void Sprite::setSpriteY(int newSpriteY){
	this->spriteY = newSpriteY;
}

int Sprite::getSpriteY(){
	return this->spriteY;
}

Sprite::~Sprite() {}
