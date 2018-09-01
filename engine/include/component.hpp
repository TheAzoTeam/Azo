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

			virtual void shutdown();

			virtual void Draw();

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
