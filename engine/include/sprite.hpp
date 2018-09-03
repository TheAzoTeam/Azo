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