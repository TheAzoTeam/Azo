#ifndef OBSTACLE
#define OBSTACLE

#include "game_object.hpp"
#include "invisible_block.hpp"
#include "machine_part_code.hpp"

namespace Azo {

	// Add new Obstacle Types here.
	enum class ObstacleType {
		GROUND,
		WESTERN_BOX,
		WESTERN_RAISED_BOX,
		WESTERN_CAR,
		WESTERN_ROCK,
		WESTERN_SPIKE,
		MACHINE_PART,
	};

	enum class MachinePartState {
		COLLECTED,
		NON_COLLECTED,
		NON_MACHINE,
		FINISHED,
	};

	class Obstacle : public engine::GameObject {
		public:
			std::pair<double, double> m_position_relative_to_parent;
			std::list<InvisibleBlock *> m_block_list;
			ObstacleType m_obstacle_type;
			MachinePartState m_machine_part_state = MachinePartState::NON_MACHINE;
		private:
			engine::ImageComponent *m_obstacle_image;

			engine::AudioController *m_audio_controller;

			engine::Animation *m_turning;

			engine::AudioComponent *m_collected;

			std::vector<engine::Sprite *> m_turning_animation_sprites;

			MachinePartCode *m_machine_part_code;
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
