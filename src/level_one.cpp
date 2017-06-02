#include "level_one.hpp"

using namespace Azo;

LevelOne::LevelOne(){}

LevelOne::LevelOne(std::string name){
	this->scene_name = name;
	SetDependencies();
}

void LevelOne::SetDependencies(){
	CreateGameObjects();
	SetGameObjects();
}

void LevelOne::CreateGameObjects(){
	player = new Player("McCree", 0, 300);
	floor_platform = new Floor("floor", 0, 500);
	wall = new Wall("wall", 500, 430);
	floor_plataform_two = new Floor("floor_2", 1259, 500);
}

void LevelOne::SetGameObjects(){
	this->AddGameObject(*player);
	this->AddGameObject(*floor_platform);
	this->AddGameObject(*wall);
	this->AddGameObject(*floor_plataform_two);
}

void LevelOne::Shutdown(){
	DestroyGameObjects();
}

void LevelOne::DestroyGameObjects(){
	player->Shutdown();
	free(player);
	player = NULL;

	floor_platform->Shutdown();
	free(floor_platform);
	floor_platform = NULL;

	wall->Shutdown();
	free(wall);
	wall = NULL;

}
