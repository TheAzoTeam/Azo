#include "game.hpp"
#include "game_globals.hpp"
#include "level_one.hpp"
#include "menu.hpp"

using namespace Azo;

int main(int, char**) {
	// Get the Primary Data for create the game and transfer to SDL do this.
	engine::Game::instance.setAttributes(
		global::game_name,
		global::window_width,
		global::window_height,
		global::frame_rate);

	LevelOne level_one("level_one");
	Menu menu("menu");

	engine::Game::instance.addScene(level_one);
	engine::Game::instance.addScene(menu);

	engine::Game::instance.changeScene("menu");

	engine::Game::instance.run();

	return 0;
}
