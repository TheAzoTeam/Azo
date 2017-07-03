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
		WESTERN_ROCK,
		MACHINE_PART,
	};

	class Obstacle : public engine::GameObject {
		public:
			std::pair<double, double> m_position_relative_to_parent;
			std::list<InvisibleBlock *> m_block_list;
			ObstacleType m_obstacle_type;
		private:
			engine::ImageComponent *m_obstacle_image;

			engine::AnimationController m_animation_controller; // For the machine part.

			// If needed, add new animations here.
			engine::Animation *m_turning; // For the machine part.

			// If needed, add new animation vectors here.
			std::vector<engine::Sprite *> m_turning_animation_sprites; // For the machine part.
		public:
			Obstacle();
			Obstacle(std::string name, std::pair<double, double> position_relative_to_parent, ObstacleType obstacle_type);
			inline std::string GetClassName(){
				return "Obstacle";
			}
		private:
			void CreateComponents();
			void CreateBlocks();
			void GenTurningAnimation();

	};
}

#endif