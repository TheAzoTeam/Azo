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
		WESTERN_POST
	};

	enum class MachinePartState {
		COLLECTED,
		NON_COLLECTED,
		NON_MACHINE,
		FINISHED,
	};

	class Obstacle : public engine::GameObject {
		public:
			std::pair<double, double> mPositionRelativeToParent;
			std::list<InvisibleBlock *> mBlockList;
			ObstacleType mObstacleType;
			MachinePartState mMachinePartState = MachinePartState::NON_MACHINE;
		private:
			engine::ImageComponent *m_obstacle_image = NULL;

			engine::AudioController *m_audio_controller = NULL;

			engine::Animation *m_turning = NULL;

			engine::AudioComponent *m_collected = NULL;

			std::vector<engine::Sprite *> m_turning_animation_sprites;

			MachinePartCode *m_machine_part_code = NULL;
		public:
			Obstacle();
			virtual ~Obstacle();
			Obstacle(std::string name, std::pair<double, double> position_relative_to_parent, ObstacleType obstacle_type);
			void Shutdown();
			inline std::string getClassName(){
				return "Obstacle";
			}
		private:
			void CreateComponents();
			void CreateBlocks();
			void GenTurningAnimation();

	};
}

#endif
