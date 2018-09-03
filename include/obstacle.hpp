#ifndef OBSTACLE
#define OBSTACLE

#include "game_object.hpp"
#include "invisible_block.hpp"
#include "machine_part_code.hpp"

namespace Azo {

	// Add new obstacle Types here.
	enum class obstacleType {
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

	class obstacle : public engine::GameObject {
		public:
			std::pair<double, double> mPositionRelativeToParent;
			std::list<InvisibleBlock *> mBlockList;
			obstacleType mobstacleType;
			MachinePartState mMachinePartState = MachinePartState::NON_MACHINE;
		private:
			engine::ImageComponent *mobstacleImage = NULL;

			engine::AudioController *mAudioController = NULL;

			engine::Animation *mTurning = NULL;

			engine::AudioComponent *mCollected = NULL;

			std::vector<engine::Sprite *> mTurningAnimationSprites;

			machinePartCode *mMachinePartCode = NULL;
		public:
			obstacle();
			virtual ~obstacle();
			obstacle(std::string name, std::pair<double, double> positionRelativeToParent, obstacleType obstacleType);
			void shutDown();
			inline std::string getClassName(){
				return "obstacle";
			}
		private:
			void createComponents();
			void createBlocks();
			void generateTurningAnimation();

	};
}

#endif
