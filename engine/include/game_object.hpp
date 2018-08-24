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
		std::pair<double, double> m_current_position; 
		/* m_current_position is the left upper corner of the game object, 
		in coordinates. */
		std::pair<double, double> m_size; 
		/* m_size.first and m_size.second correspond to the X and Y sizes, 
		respectively. */
		std::pair<double, double> m_center; // Center position of game object.
		std::pair<double, double> m_half_size; // Same as m_size.
		std::list<GameObject *> m_parent_list;
		std::string m_name;
		ObjectState m_object_state = ObjectState::ENABLED;

	protected:
		std::unordered_multimap<std::type_index, Component *> m_component_map;

	public:
		GameObject();
		GameObject(std::string game_object_name, 
				   std::pair<double, double> current_position);
		void addComponent(Component &component);
		AnimationController* getAnimationController(std::type_index component_type);
		AudioController* getAudioController(std::type_index component_type);
		virtual void init();
		virtual void draw();
		virtual void shutdown();
		virtual void updateCode();
		virtual inline std::string getClassName(){ return "GameObject";}
		std::pair<double, double> calcBottomLeft();
		std::pair<double, double> calcBottomRight();
		std::pair<double, double> calcTopLeft();
		std::pair<double, double> calcTopRight();
		std::pair<double, double> calcRightUp();
		std::pair<double, double> calcRightDown();
		std::pair<double, double> calcLeftUp();
		std::pair<double, double> calcLeftDown();
	};

}

#endif