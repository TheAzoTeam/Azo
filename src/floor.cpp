#include "floor.hpp"

using namespace Azo;

Floor::Floor(){}

Floor::Floor(std::string name, int x, int y){
	this->game_object_name = name;
	this->x = x;
	this->y = y;
	SetDependencies();
}

void Floor::SetDependencies(){
	CreateComponents();
	SetComponents();
}

void Floor::CreateComponents(){
	floor_image = new engine::ImageComponent(*this, "sprites/floor.png");
}

void Floor::SetComponents(){
	ASSERT(floor_image != NULL, "Floor image can't be NULL while setting components.");

	this->AddComponent(*floor_image);
}


bool Floor::Shutdown(){
	ASSERT(floor_image != NULL, "Floor image can't be NULL while shutting down.");

	floor_image->Shutdown();
	free(floor_image);
	floor_image = NULL;

	return true;
}