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
	player.SetCode(player);

	engine::Scene player_scene("player_scene");
	player_scene.AddGameObject(player);

	engine::Game::instance.AddScene(player_scene);

	engine::Game::instance.Run();
	return 0;
}
