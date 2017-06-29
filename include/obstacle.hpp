#ifndef OBSTACLE
#define OBSTACLE

#include "game_object.hpp"
#include "invisible_block.hpp"

namespace Azo {

	// Add new Obstacle Types here.
	enum class ObstacleType {
		GROUND,
		WESTERN_BOX,
		WESTERN_CAR,
	};

	class Obstacle : public engine::GameObject {
		public:
			std::pair<double, double> m_position_relative_to_parent;
			std::list<InvisibleBlock *> m_block_list;
		private:
			engine::ImageComponent *m_obstacle_image;
			ObstacleType m_obstacle_type;
		public:
			Obstacle();
			Obstacle(std::string name, std::pair<double, double> position_relative_to_parent, ObstacleType obstacle_type);
			inline std::string GetClassName(){
				return "Obstacle";
			}
		private:
			void CreateComponents();
			void CreateBlocks();
	};
}

#endif