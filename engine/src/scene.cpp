#include "scene.hpp"

using namespace engine;

Scene::Scene(){}

Scene::Scene(std::string scene_name){
	this->scene_name = scene_name;
}


void Scene::Init(){
	for(auto each_key : m_key_list){
		gameObject_map[each_key]->Init();
	}
}

void Scene::shutDown(){
	for(auto each_key : m_key_list){
		gameObject_map[each_key]->shutDown();
	}

	DeleteKeyList();
}

void Scene::DeleteKeyList(){
	m_key_list.erase(m_key_list.begin(), m_key_list.end());
}


void Scene::Draw(){
	for(auto each_key : m_key_list){
		if(gameObject_map[each_key]->mObjectState == ObjectState::ENABLED){
			gameObject_map[each_key]->Draw();
		}
	}
}

void Scene::updateCode(){
	for(auto each_key : m_key_list){
		if(gameObject_map[each_key]->mObjectState == ObjectState::ENABLED){
			gameObject_map[each_key]->updateCode();
		}
	}
}

void Scene::Restart(){}

void Scene::AddGameObject(GameObject &gameObject){
	auto gameObject_name = gameObject.mName;

	if(gameObject_map.find(gameObject_name) != gameObject_map.end()){
		ERROR("Game object already exists!");
	}

	gameObject_map[gameObject_name] = &gameObject;
	m_key_list.push_back(gameObject_name);
}

GameObject & Scene::GetGameObject(std::string &gameObject_name){

	if(gameObject_map.find(gameObject_name) == gameObject_map.end()){
		ERROR("Game object doesn't exist!");
	}

	return *gameObject_map[gameObject_name];

}

void Scene::RemoveGameObject(std::string &gameObject_name){
	if(gameObject_map.find(gameObject_name) == gameObject_map.end()){
		ERROR("Game object doesn't exist!");
	}

	gameObject_map.erase(gameObject_name);

	m_key_list.remove(gameObject_name);

}
