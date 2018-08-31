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
			std::string animationName;
			AnimationState m_state = AnimationState::STOPPED;
		public:
			Animation();
			virtual ~Animation();
			void Shutdown();
			Animation(
				GameObject & gameObject,
				std::string imagePath,
				float animation_time,
				std::vector<Sprite *> sprite_list,
				int start_frame,
				int end_frame,
				bool loop,
				double zoomFactor);

			Animation(
				GameObject & gameObject,
				std::string imagePath,
				float animation_time,
				std::vector<Sprite *> sprite_list,
				int start_frame,
				int end_frame,
				bool loop,
				double zoomFactor,
				std::pair<double, double> positionRelativeToObject);
			void Draw();
			inline std::string GetClassName(){
				return "Animation";
			}
			void DisableComponent();

		private:
			void CheckLimits();
			void UpdateQuad();
			void UpdateFrameBasedOntime();
			void UpdateGameObjectMeasures();
	};

}

#endif
