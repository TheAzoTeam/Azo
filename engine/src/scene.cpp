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
		if(ResolveCollision() == true){
			game_object->ResolveCollision();
		}
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

bool Scene::ResolveCollision(){
	auto game_object = game_object_map.find("McCree")->second;

	for(auto each_row : game_object_map){
		auto each_game_object = each_row.second;
		if(each_game_object->GetGameObjectName() != "McCree"){
			if(game_object->bottom <= each_game_object->top){
				return false;
			}

			if(game_object->top >= each_game_object->bottom){
				return false;
			}

			if(game_object->right <= each_game_object->left){
				return false;
			}

			if(game_object->left >= each_game_object->right){
				return false;
			}
		}
	}

	return true;

}

