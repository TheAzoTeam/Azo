#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

namespace engine {

	class GameObject;

	class Component {
		protected:
			GameObject *game_object;

		public:
			Component();

			Component(GameObject &game_object);

			~Component();

			virtual bool Init();

			virtual bool Shutdown();
	};
}

#endif
