#include "game.hpp"
#include "game_globals.hpp"
#include "player.hpp"

using namespace Azo;

int main(int, char**) {
	// Get the Primary Data for create the game and transfer to SDL do this.
	engine::Game::instance.SetAttributes(
		global::game_name,
		global::window_width,
		global::window_height,
		global::frame_rate);

	engine::Scene level_one("level_one");

	Player new_player("new_player", std::make_pair(300, 300));

	level_one.AddGameObject(new_player);

	engine::Game::instance.AddScene(level_one);
	engine::Game::instance.ChangeScene("level_one");

	engine::Game::instance.Run();

	return 0;
}
