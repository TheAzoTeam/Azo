#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include "sdl2include.h"
#include "moving_image_component.hpp"
#include "sprite.hpp"

#include <vector>


namespace engine {
	class Animation : public MovingImageComponent {
		private:
			std::vector<Sprite *> sprite_list;
			int current_sprite;
			int start_frame;
			int end_frame;
			float current_animation_time;
			int each_frame_time;
			float animation_time;
		public:
			std::string animation_name;

		public:
			Animation();
			~Animation();
			Animation(
				GameObject & game_object,
				std::string image_path,
				float animation_time,
				std::vector<Sprite *> sprite_list,
				int start_frame,
				int end_frame);
			void Draw();

		private:
			void UpdateQuad();
			void CheckLimits();
			void UpdateFrameBasedOntime();
			void UpdateGameObjectMeasures();
	};

}

#endif
