#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

namespace engine {

	class GameObject;

	class Component {
		public:
			Component();
			Component(GameObject &game_object) : game_object(&game_object){
			}
			~Component();

			virtual bool Init();
			virtual bool Shutdown();
		protected:
			GameObject *game_object;
	};
}

#endif