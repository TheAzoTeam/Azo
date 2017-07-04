#include "scene.hpp"

using namespace engine;

Scene::Scene(){}

Scene::Scene(std::string scene_name){
	this->scene_name = scene_name;
}


void Scene::Init(){
	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		game_object->Init();
	}
}

void Scene::Shutdown(){
	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		game_object->Shutdown();
	}
}

void Scene::Draw(){
	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		if(game_object->m_object_state == ObjectState::ENABLED){
			game_object->Draw();
		}

	}
}

void Scene::UpdateCode(){
	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		if(game_object->m_object_state == ObjectState::ENABLED){
			game_object->UpdateCode();
		}
	}
}


void Scene::Restart(){}

void Scene::AddGameObject(GameObject &game_object){
	auto game_object_name = game_object.m_name;

	if(game_object_map.find(game_object_name) != game_object_map.end()){
		ERROR("Game object already exists!");
	}

	game_object_map[game_object_name] = &game_object;
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

}