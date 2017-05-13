#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

namespace engine {

	class GameObject;

	enum class State {
		ENABLED,
		DISABLED
	};

	class Component {
		protected:
			GameObject *game_object;
			State component_state;

		public:
			Component();

			Component(GameObject &game_object);

			~Component();

			virtual bool Init();

			virtual bool Shutdown();

			virtual bool Draw();

			virtual bool UpdateCode();
	};
}

#endif
