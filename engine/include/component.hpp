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
			GameObject *gameObject;
			State componentState = State::ENABLED;

		public:
			Component();

			Component(GameObject &gameObject);

			virtual void Init();

			virtual void shutdown();

			virtual void draw();

			virtual void UpdateCode();

			virtual void EnableComponent();

			virtual void disableComponent();

			bool IsEnabled();

			virtual inline std::string getClassName(){
				return "Component";
			}
	};
}

#endif
