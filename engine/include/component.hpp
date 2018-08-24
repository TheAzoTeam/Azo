#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

#include <string>

namespace engine {

	class GameObject;

	enum class State {
		ENABLED,
		DISABLED
	};

	class Component {

	protected:
		GameObject *game_object;
		State component_state = State::ENABLED;
	public:
		Component();
		Component(GameObject &game_object);
		virtual void init();
		virtual void shutdown();
		virtual void draw();
		virtual void updateCode();
		virtual void enableComponent();
		virtual void disableComponent();
		bool isEnabled();
		virtual inline std::string getClassName(){ return "Component"; }
	};
}

#endif
