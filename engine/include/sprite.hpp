/**
 * @file sprite.hpp
 * @brief Purpose: Contains the components of the sprite.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 * 
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 * 
 * This file implements the main sprite component its declaration and state.
*/
#ifndef SPRITE_HPP
#define SPRITE_HPP

namespace engine {
	class Sprite {
		public:
			Sprite();
			Sprite(int spriteWidth, int spriteHeight, int spriteX, int spriteY);
			~Sprite();
		public:
			int spriteWidth;
			int spriteHeight;
			int spriteX;
			int spriteY;
	};
}

#endif
