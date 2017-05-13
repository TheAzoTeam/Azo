#include "scene.hpp"

using namespace engine;

Scene::Scene(){}

Scene::Scene(std::string scene_name){
	this->scene_name = scene_name;
}


bool Scene::Init(){
	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		if(game_object->Init() == false){
			return false;
		}
	}
	return true;
}

bool Scene::Shutdown(){
	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		if(game_object->Shutdown() == false){
			return false;
		}
	}
	return true;
}

bool Scene::Draw(){
	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		if(game_object->Draw() == false){
			return false;
		}
	}
	return true;
}

bool Scene::AddGameObject(GameObject &game_object){
	auto game_object_name = game_object.GetGameObjectName();

	if(game_object_map.find(game_object_name) != game_object_map.end()){
		std::cout << "Game object already exists!" << std::endl;
		return false;
	}

	game_object_map[game_object_name] = &game_object;
	return true;
}

GameObject & Scene::GetGameObject(std::string &game_object_name){

	if(game_object_map.find(game_object_name) == game_object_map.end()){
		std::cout << "Game object doesn't exist!" << std::endl;
	}

	return *game_object_map[game_object_name];

}

bool Scene::RemoveGameObject(std::string &game_object_name){
	if(game_object_map.find(game_object_name) == game_object_map.end()){
		std::cout << "Game object doesn't exist!" << std::endl;
		return false;
	}

	game_object_map.erase(game_object_name);
	return true;

}
