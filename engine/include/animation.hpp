#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include "sdl2include.h"
#include "image_component.hpp"


namespace engine {
	class Animation : public ImageComponent {
		private:
			int current_frame;
			int starting_frame;
			int ending_frame;
			int sprite_rows;
			int sprite_colums;
			float frame_time;
			float total_frames;
			float animation_time;
			float current_animation_time;

		public:
			Animation();

			void CreateAnimation(
				GameObject &game_object,
				std::string image_path,
				float animation_time,
				int sprite_rows,
				int sprite_colums,
				int starting_frame,
				int ending_frame);

			~Animation();

			// Define frames of animation from sprites
			bool Draw();
	};
}

#endif
