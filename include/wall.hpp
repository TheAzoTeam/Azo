#ifndef WALL_HPP
#define WALL_HPP

#include "game_object.hpp"
#include "wall_code.hpp"

namespace Azo {
	class Wall : public engine::GameObject {
		private:
			engine::ImageComponent *wall_image;

			WallCode *wall_code;
		public:
			Wall();
			Wall(std::string name, int x, int y);
			void SetDependencies();
			void CreateComponents();
			void SetComponents();
			bool Shutdown();
	};
}

#endif