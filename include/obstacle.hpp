#ifndef OBSTACLE
#define OBSTACLE

#include "game_object.hpp"

namespace Azo {
	class Obstacle : public engine::GameObject {
		public:
			std::pair<double, double> m_position_relative_to_parent;
		private:
			engine::ImageComponent *m_obstacle_image;
		public:
			Obstacle();
			Obstacle(std::string name, std::pair<double, double> position_relative_to_parent);
			inline std::string GetClassName(){
				return "Obstacle";
			}
		private:
			void CreateComponents();

	};
}

#endif