#include "wall.hpp"

using namespace Azo;

Wall::Wall(){}

Wall::Wall(std::string name, int x, int y){
	this->game_object_name = name;
	this->x = x;
	this->y = y;
	SetDependencies();
}

void Wall::SetDependencies(){
	CreateComponents();
	SetComponents();
}

void Wall::CreateComponents(){
	wall_image = new engine::MovingImageComponent(*this, "sprites/wall.png");
	wall_code = new WallCode(*this);
}

void Wall::SetComponents(){
	ASSERT(wall_image != NULL, "Wall image can't be NULL while setting components.");
	ASSERT(wall_code != NULL, "Wall Code can't be NULL while setting components.");

	this->AddComponent(*wall_image);
	this->AddComponent(*wall_code);
}


void Wall::Shutdown(){
	ASSERT(wall_image != NULL, "Wall image can't be NULL while shutting down.");
	ASSERT(wall_code != NULL, "Wall Code can't be NULL while shutting down.");

	wall_image->Shutdown();
	free(wall_image);
	wall_image = NULL;

	wall_code->Shutdown();
	free(wall_code);
	wall_code = NULL;

}