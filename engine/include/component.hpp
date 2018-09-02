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

			virtual void Shutdown();

			virtual void Draw();

			virtual void UpdateCode();

			virtual void EnableComponent();

			virtual void DisableComponent();

			bool isEnabled();

			virtual inline std::string GetClassName(){
				return "Component";
			}
	};
}

#endif
