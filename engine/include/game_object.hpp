#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <list>

#include "animation.hpp"
#include "sdl2include.h"
#include "component.hpp"
#include "animation_controller.hpp"
#include "audio_controller.hpp"

namespace engine {

	enum ObjectState {
		ENABLED,
		DISABLED,
	};

	class GameObject {
		public:
			// mCurrentPosition is the left upper corner of the game object, in coordinates.
			std::pair<double, double> mCurrentPosition;
			// mSize.first is the X size.
			// m_sisze.second is the Y size.
			std::pair<double, double> mSize;
			std::pair<double, double> mCenter;
			// mHalfSize.first is the x distance from center to the border.
			// mHalfSize.second is the y distance from center to the border.
			std::pair<double, double> mHalfSize;
			std::list<GameObject *> m_parent_list;
			std::string mName;
			ObjectState m_object_state = ObjectState::ENABLED;

		protected:
			std::unordered_multimap<std::type_index, Component *> m_component_map;

		public:
			GameObject();
			GameObject(std::string game_object_name, std::pair<double, double> current_position);
			void addComponent(Component &component);
			AnimationController* GetAnimationController(std::type_index component_type);
			AudioController* GetAudioController(std::type_index component_type);
			virtual void Init();
			virtual void Draw();
			virtual void shutdown();
			virtual void UpdateCode();
			virtual inline std::string getClassName(){
				return "GameObject";
			}
			std::pair<double, double> CalcBottomLeft();
			std::pair<double, double> CalcBottomRight();
			std::pair<double, double> CalcTopLeft();
			std::pair<double, double> CalcTopRight();
			std::pair<double, double> CalcRightUp();
			std::pair<double, double> CalcRightDown();
			std::pair<double, double> CalcLeftUp();
			std::pair<double, double> CalcLeftDown();
	};

}

#endif