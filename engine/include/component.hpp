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
			State component_state = State::ENABLED;

		public:
			Component();

			Component(GameObject &gameObject);

			virtual void Init();

			virtual void shutDown();

			virtual void Draw();

			virtual void updateCode();

			virtual void EnableComponent();

			virtual void DisableComponent();

			bool IsEnabled();

			virtual inline std::string getClassName(){
				return "Component";
			}
	};
}

#endif
