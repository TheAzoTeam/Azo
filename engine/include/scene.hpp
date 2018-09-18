#ifndef SCENE_ENGINE_HPP
#define SCENE_ENGINE_HPP

#include <iostream>
#include <unordered_map>
#include "sdl2include.h"
#include "game_object.hpp"

namespace engine {

	enum class SceneState {
		FIRST_TIME,
		RUNNED,
	};

	class Scene {
	public:
		Scene();
		Scene(std::string sceneName);

		virtual void init();
		virtual void shutdown();
		virtual void draw();
		virtual void updateCode();
		virtual void restart();

		inline std::string getSceneName() {
			return sceneName;
		}

		void deleteKeyList();
		void addGameObject(engine::GameObject &gameObject);
		void removeGameObject(std::string &gameObjectName);
		engine::GameObject & getGameObject(std::string & gameObjectName);
		SceneState mState = SceneState::FIRST_TIME;

	protected:
		std::map<std::string, engine::GameObject *> gameObjectMap;
		std::list<std::string> mKeyList;
		std::string sceneName;
	};
}

#endif
