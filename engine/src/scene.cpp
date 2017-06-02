#include "scene.hpp"

using namespace engine;

Scene::Scene(){}

Scene::Scene(std::string scene_name){
	this->scene_name = scene_name;
}


void Scene::Init(){
	DEBUG("Init Scene name: " << this->GetSceneName());
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
	//DEBUG("Draw Scene Name. " << this->GetSceneName());
	ResolveCollision();

	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		game_object->Draw();
	}
}

void Scene::UpdateCode(){
	for(auto each_game_object : game_object_map){
		auto game_object = each_game_object.second;
		game_object->UpdateCode();
	}
}


void Scene::AddGameObject(GameObject &game_object){
	auto game_object_name = game_object.GetGameObjectName();

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

void Scene::ResolveCollision(){
	std::unordered_map<std::string, engine::GameObject *>::iterator iterator_one;
	std::unordered_map<std::string, engine::GameObject *>::iterator iterator_two;

	// Iterate through game_object_map, comparing each element with the subsequent ones.
	for(iterator_one = game_object_map.begin(); iterator_one != game_object_map.end(); ++iterator_one){
		auto game_object_one = iterator_one->second;

		for(iterator_two = std::next(iterator_one); iterator_two != game_object_map.end(); ++iterator_two){
			auto game_object_two = iterator_two->second;

			// Check if the objects are colliding.
			if(game_object_one->bottom <= game_object_two->top){
				game_object_one->state = GameObjectState::NOT_COLLIDING;

			}else if(game_object_one->top >= game_object_two->bottom){
				game_object_one->state = GameObjectState::NOT_COLLIDING;

			}else if(game_object_one->right <= game_object_two->left){
				game_object_one->state = GameObjectState::NOT_COLLIDING;

			}else if(game_object_one->left >= game_object_two->right){
				game_object_one->state = GameObjectState::NOT_COLLIDING;

			}else{
				//		INFO("Game object one: " << game_object_one->GetGameObjectName());
				//	INFO("Game object two: " << game_object_two->GetGameObjectName());

				game_object_one->state = GameObjectState::COLLIDING;
				game_object_two->state = GameObjectState::COLLIDING;
				game_object_one->collision_list.push_back(game_object_two->GetClassName());
				game_object_two->collision_list.push_back(game_object_one->GetClassName());

			}
		}
	}
}
