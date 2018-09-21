/** 
 * @file component.hpp
 * @brief Purpose: Contains the Component class declaration.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

#include <string>


namespace engine {
	/**
     * @brief A GameObject class.
  	 *
     * Reference to GameObject class.
    */
	class GameObject;

	/**
     * @brief A Hitbox class.
  	 *
     * Define Components States to control Loops and other strutuctures.
    */
	enum class State {
		ENABLED,
		DISABLED
	};

	/**
     * @brief A Component class.
  	 *
     * Generic Component class. It's how the engine'll see all components that will try to use it.
    */
	class Component {

		protected:
			GameObject *gameObject; // represents the object of the game
			State componentState = State::ENABLED; // set the component state (based on enum class State)
		public:
			Component();
			Component(GameObject &gameObject);
			virtual void init();
			virtual void shutdown();
			virtual void draw();
			virtual void updateCode();
			virtual void enableComponent();
			virtual void disableComponent();
			bool isEnabled();

			/**
			 * @brief access the name of the class.
			 *  
			 * Used to get the private attribute className.
			 * 
			 * @return string that contains the scene name.
			*/
			virtual inline std::string getClassName(){
				return "Component";
			}
	};
}

#endif
