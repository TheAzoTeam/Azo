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

			virtual void Init();

			virtual void Shutdown();

			virtual void Draw();

			virtual void updateCode();

			virtual void EnableComponent();

			virtual void DisableComponent();

			bool IsEnabled();

			virtual inline std::string GetClassName(){
				return "Component";
			}
	};
}

#endif
