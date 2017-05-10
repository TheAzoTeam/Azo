#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

namespace engine {

	enum class State {
		ENABLED,
		DISABLED
	};

	class GameObject;

	class Component {
		public:
			State component_state;

		protected:
			GameObject *game_object;

		public:
			Component();

			Component(GameObject &game_object) : game_object(&game_object){}

			~Component();

			virtual bool Init();

			virtual bool Shutdown();

			void EnableComponent();

			void DisableComponent();

	};
}

#endif
