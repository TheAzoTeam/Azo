#ifndef SPRITE_HPP
#define SPRITE_HPP

namespace engine {
	class Sprite {
		public:
			Sprite();
			Sprite(int sprite_width, int sprite_height, int sprite_x, int sprite_y);
			~Sprite();
		public:
			int sprite_width;
			int sprite_height;
			int sprite_x;
			int sprite_y;
	};
}

#endif