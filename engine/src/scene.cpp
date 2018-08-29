#include "scene.hpp"

using namespace engine;

Scene::Scene(){}

Scene::Scene(std::string scene_name){
	this->scene_name = scene_name;
}


void Scene::Init(){
	for(auto each_key : m_key_list){
		gameObjectMap[each_key]->Init();
	}
}

void Scene::Shutdown(){
	for(auto each_key : m_key_list){
		gameObjectMap[each_key]->Shutdown();
	}

	DeleteKeyList();
}

void Scene::DeleteKeyList(){
	m_key_list.erase(m_key_list.begin(), m_key_list.end());
}


void Scene::Draw(){
	for(auto each_key : m_key_list){
		if(gameObjectMap[each_key]->m_object_state == ObjectState::ENABLED){
			gameObjectMap[each_key]->Draw();
		}
	}
}

void Scene::UpdateCode(){
	for(auto each_key : m_key_list){
		if(gameObjectMap[each_key]->m_object_state == ObjectState::ENABLED){
			gameObjectMap[each_key]->UpdateCode();
		}
	}
}

void Scene::Restart(){}

void Scene::AddGameObject(GameObject &gameObject){
	auto gameObject_name = gameObject.m_name;

	if(gameObjectMap.find(gameObject_name) != gameObjectMap.end()){
		ERROR("Game object already exists!");
	}

	gameObjectMap[gameObject_name] = &gameObject;
	m_key_list.push_back(gameObject_name);
}

GameObject & Scene::GetGameObject(std::string &gameObject_name){

	if(gameObjectMap.find(gameObject_name) == gameObjectMap.end()){
		ERROR("Game object doesn't exist!");
	}

	return *gameObjectMap[gameObject_name];

}

void Scene::RemoveGameObject(std::string &gameObject_name){
	if(gameObjectMap.find(gameObject_name) == gameObjectMap.end()){
		ERROR("Game object doesn't exist!");
	}

	gameObjectMap.erase(gameObject_name);

	m_key_list.remove(gameObject_name);

}
