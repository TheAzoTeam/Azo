#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include "sdl2include.h"
#include "image_component.hpp"
#include "sprite.hpp"

#include <vector>


namespace engine {

	enum class AnimationState {
		PLAYING,
		STOPPED,
		FINISHED,
	};

	class Animation : public ImageComponent {
		private:
			std::vector<Sprite *> m_sprite_list;
			int m_current_sprite;
			int m_start_frame;
			int m_end_frame;
			float m_current_animation_time;
			int m_each_frame_time;
			float m_animation_time;
			bool m_loop;
		public:
			std::string animation_name;
			AnimationState mState = AnimationState::STOPPED;
		public:
			Animation();
			virtual ~Animation();
			void shutdown();
			Animation(
				GameObject & game_object,
				std::string image_path,
				float animation_time,
				std::vector<Sprite *> sprite_list,
				int start_frame,
				int end_frame,
				bool loop,
				double zoom_factor);

			Animation(
				GameObject & game_object,
				std::string image_path,
				float animation_time,
				std::vector<Sprite *> sprite_list,
				int start_frame,
				int end_frame,
				bool loop,
				double zoom_factor,
				std::pair<double, double> position_relative_to_object);
			void Draw();
			inline std::string GetClassName(){
				return "Animation";
			}
			void disableComponent();

		private:
			void CheckLimits();
			void UpdateQuad();
			void UpdateFrameBasedOntime();
			void UpdateGameObjectMeasures();
	};

}

#endif
