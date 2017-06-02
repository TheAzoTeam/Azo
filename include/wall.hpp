#ifndef WALL_HPP
#define WALL_HPP

#include "game_object.hpp"
#include "wall_code.hpp"
#include "moving_image_component.hpp"

namespace Azo {
	class Wall : public engine::GameObject {
		private:
			engine::MovingImageComponent *wall_image;

			WallCode *wall_code;
		public:
			Wall();
			Wall(std::string name, int x, int y);
			void SetDependencies();
			void CreateComponents();
			void SetComponents();
			void Shutdown();
			inline std::string GetClassName(){
				return "Wall";
			}
	};
}

#endif