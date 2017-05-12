#include "game.hpp"
#include "game_globals.hpp"
#include "code_component.hpp"
#include "player.hpp"
using namespace Azo;

int main(int, char**) {
	engine::Game::instance.SetAttributes(
		global::game_name,
		global::window_width,
		global::window_height,
		global::frame_rate);

	Player player("McCree");
	player.SetAnimations(player);

	//TODO(Roger): Create class which implements player movement.
	// engine::CodeComponent player_movement(player);
	// player.AddComponent(player_movement);

	engine::Scene player_scene("player_scene");
	player_scene.AddGameObject(player);

	engine::Game::instance.AddScene(player_scene);

	engine::Game::instance.Run();
	return 0;
}
