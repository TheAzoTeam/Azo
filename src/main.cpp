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
	Player player("McCree", 150, 150);

	engine::Scene player_scene("player_scene");
	player_scene.AddGameObject(player);
	engine::Game::instance.AddScene(player_scene);

	engine::Game::instance.Run();
	return 0;
}
