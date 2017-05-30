#include "game.hpp"
#include "game_globals.hpp"
#include "code_component.hpp"
#include "player.hpp"

using namespace Azo;


int main(int, char**) {
	// Get the Primary Data for create the game and transfer to SDL do this.
	engine::Game::instance.SetAttributes(
		global::game_name,
		global::window_width,
		global::window_height,
		global::frame_rate);

	// Creating a game object player, Setting Animations to Animation Controller and Setting specific codes.
	Player player("McCree", -250, 380);
	engine::GameObject box("box", 600, 500);

	// Adding Components to respectives game objects.
	engine::ImageComponent box_image(box, "sprites/blackbox.jpeg");
	box.AddComponent(box_image);

	// Creating Scenes.
	engine::Scene player_scene("player_scene");

	// Adding game objects to respectives Scenes.
	player_scene.AddGameObject(player);
	player_scene.AddGameObject(box);

	// Adding Scenes to game.
	engine::Game::instance.AddScene(player_scene);

	// Starting game execution.
	engine::Game::instance.Run();

	return 0;
}
