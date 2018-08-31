#include "scene.hpp"

using namespace engine;

Scene::Scene(){}

Scene::Scene(std::string scene_name){
	this->scene_name = scene_name;
}


void Scene::init(){
	for(auto each_key : m_key_list){
		game_object_map[each_key]->init();
	}
}

void Scene::shutdown(){
	for(auto each_key : m_key_list){
		game_object_map[each_key]->shutdown();
	}

	DeleteKeyList();
}

void Scene::DeleteKeyList(){
	m_key_list.erase(m_key_list.begin(), m_key_list.end());
}


void Scene::draw(){
	for(auto each_key : m_key_list){
		if(game_object_map[each_key]->mObjectState == ObjectState::ENABLED){
			game_object_map[each_key]->draw();
		}
	}
}

void Scene::updateCode(){
	for(auto each_key : m_key_list){
		if(game_object_map[each_key]->mObjectState == ObjectState::ENABLED){
			game_object_map[each_key]->updateCode();
		}
	}
}

void Scene::Restart(){}

void Scene::AddGameObject(GameObject &game_object){
	auto game_object_name = game_object.mName;

	if(game_object_map.find(game_object_name) != game_object_map.end()){
		ERROR("Game object already exists!");
	}

	game_object_map[game_object_name] = &game_object;
	m_key_list.push_back(game_object_name);
}

GameObject & Scene::GetGameObject(std::string &game_object_name){

	if(game_object_map.find(game_object_name) == game_object_map.end()){
		ERROR("Game object doesn't exist!");
	}

	return *game_object_map[game_object_name];

}

void Scene::RemoveGameObject(std::string &game_object_name){
	if(game_object_map.find(game_object_name) == game_object_map.end()){
		ERROR("Game object doesn't exist!");
	}

	game_object_map.erase(game_object_name);

	m_key_list.remove(game_object_name);

}
