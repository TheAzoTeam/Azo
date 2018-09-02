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
		std::pair<double, double> mCurrentPosition; 	
		/* mCurrentPosition is the left upper corner of the game object, 
		in coordinates. */
		std::pair<double, double> mSize; 				
		/* mSize.first and mSize.second correspond to the X and Y sizes, 
		respectively. */
		std::pair<double, double> mCenter; // Center position of game object.
		std::pair<double, double> mHalfSize; // Same as mSize. 
		std::list<GameObject *> mParentList; 
		std::string mName;	
		ObjectState mObjectState = ObjectState::ENABLED; 

	protected: 
		std::unordered_multimap<std::type_index, Component *> mComponentMap; 

	public:
		GameObject(); 
		GameObject(std::string gameObjectName, 
				   std::pair<double, double> currentPosition);
		void addComponent(Component &component); 
		AnimationController* getAnimationController(std::type_index componentType); 
		AudioController* getAudioController(std::type_index componentType); 
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