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
	floor_image = new engine::MovingImageComponent(*this, "sprites/floor.png");
	floor_code = new FloorCode(*this);
}

void Floor::SetComponents(){
	ASSERT(floor_image != NULL, "Floor image can't be NULL while setting components.");
	ASSERT(floor_code != NULL, "Floor Code can't be NULL while setting components.");

	this->AddComponent(*floor_image);
	this->AddComponent(*floor_code);
}


void Floor::Shutdown(){
	ASSERT(floor_image != NULL, "Floor image can't be NULL while shutting down.");
	ASSERT(floor_code != NULL, "Floor Code can't be NULL while shutting down.");

	floor_image->Shutdown();
	free(floor_image);
	floor_image = NULL;

	floor_code->Shutdown();
	free(floor_code);
	floor_code = NULL;

}
