#include "game.hpp"
#include "game_globals.hpp"
#include "level_one.hpp"

using namespace Azo;

int main(int, char**) {
	// Get the Primary Data for create the game and transfer to SDL do this.
	engine::Game::instance.SetAttributes(
		global::game_name,
		global::window_width,
		global::window_height,
		global::frame_rate);

	LevelOne level_one("level_one");

	engine::Game::instance.AddScene(level_one);
	engine::Game::instance.ChangeScene("level_one");

	engine::Game::instance.Run();

	return 0;
}
