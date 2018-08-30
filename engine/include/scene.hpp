#ifndef SCENE_ENGINE_HPP
#define SCENE_ENGINE_HPP

#include <iostream>
#include "sdl2include.h"
#include "game_object.hpp"
#include <unordered_map>

namespace engine {
	enum class SceneState {
		FIRST_TIME,
		RUNNED,
	};

	class Scene {
		public:
			Scene();
			Scene(std::string sceneName);

			virtual void Init();
			virtual void shutdown();
			virtual void Draw();
			virtual void UpdateCode();
			virtual void Restart();

			inline std::string GetSceneName() {
				return sceneName;
			}

			void DeleteKeyList();

			void AddGameObject(engine::GameObject &game_object);
			engine::GameObject & GetGameObject(std::string & game_object_name);
			void RemoveGameObject(std::string &game_object_name);

			SceneState mState = SceneState::FIRST_TIME;

		protected:
			std::map<std::string, engine::GameObject *>  gameObjectMap;
			std::list<std::string> m_key_list;
			std::string sceneName;
	};
}

#endif
