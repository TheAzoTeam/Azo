#ifndef MACHINE_PART
#define MACHINE_PART

#include "game_object.hpp"

namespace Azo {
	class MachinePart : public engine::GameObject {
		private:
			engine::AnimationController m_animation_controller;

			// If needed, add new animations here.
			engine::Animation *m_turning;

			// If needed, add new animation vectors here.
			std::vector<engine::Sprite *> m_turning_animation_sprites;

		public:
			std::pair<double, double> m_position_relative_to_parent;
		public:
			MachinePart();
			MachinePart(std::string name, std::pair<double, double> position_relative_to_parent);
			inline std::string GetClassName(){
				return "MachinePart";
			}
		private:
			void CreateComponents();
			void GenTurningAnimation();
	};
}

#endif