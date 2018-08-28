#include "scene.hpp"

using namespace engine;

Scene::Scene(){}

Scene::Scene(std::string sceneName){
	this->sceneName = sceneName;
}


void Scene::Init(){
	for(auto each_key : m_key_list){
		 gameObjectMap[each_key]->Init();
	}
}

void Scene::shutdown(){
	for(auto each_key : m_key_list){
		 gameObjectMap[each_key]->shutdown();
	}

	DeleteKeyList();
}

void Scene::DeleteKeyList(){
	m_key_list.erase(m_key_list.begin(), m_key_list.end());
}


void Scene::Draw(){
	for(auto each_key : m_key_list){
		if( gameObjectMap[each_key]->m_object_state == ObjectState::ENABLED){
			 gameObjectMap[each_key]->Draw();
		}
	}
}

void Scene::UpdateCode(){
	for(auto each_key : m_key_list){
		if( gameObjectMap[each_key]->m_object_state == ObjectState::ENABLED){
			 gameObjectMap[each_key]->UpdateCode();
		}
	}
}

void Scene::Restart(){}

void Scene::AddGameObject(GameObject &game_object){
	auto game_object_name = game_object.mName;

	if( gameObjectMap.find(game_object_name) !=  gameObjectMap.end()){
		ERROR("Game object already exists!");
	}

	 gameObjectMap[game_object_name] = &game_object;
	m_key_list.push_back(game_object_name);
}

GameObject & Scene::GetGameObject(std::string &game_object_name){

	if( gameObjectMap.find(game_object_name) ==  gameObjectMap.end()){
		ERROR("Game object doesn't exist!");
	}

	return * gameObjectMap[game_object_name];

}

void Scene::RemoveGameObject(std::string &game_object_name){
	if( gameObjectMap.find(game_object_name) ==  gameObjectMap.end()){
		ERROR("Game object doesn't exist!");
	}

	 gameObjectMap.erase(game_object_name);

	m_key_list.remove(game_object_name);

}
