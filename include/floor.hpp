#ifndef FLOOR_HPP
#define FLOOR_HPP

#include <string>

#include "floor_code.hpp"
#include "game_object.hpp"

namespace Azo {
	class Floor : public engine::GameObject {
		private:
			engine::ImageComponent *floor_image;

			FloorCode *floor_code;
		public:
			Floor();
			Floor(std::string name, int x, int y);
			void SetDependencies();
			void CreateComponents();
			void SetComponents();
			bool Shutdown();
	};
}

#endif