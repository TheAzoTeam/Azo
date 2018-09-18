#include "game.hpp"
#include "game_globals.hpp"
#include "level_one.hpp"
#include "menu.hpp"

using namespace Azo;

int main(int, char**) {
	// Get the Primary Data for create the game and transfer to SDL do this.
	engine::Game::instance.setAttributes(
		global::GAME_NAME,
		global::WINDOWN_WIDTH,
		global::WINDOWN_HEIGHT,
		global::FRAME_RATE);

	LevelOne level_one("level_one");
	Menu menu("menu");

	engine::Game::instance.addScene(level_one);
	engine::Game::instance.addScene(menu);

	engine::Game::instance.changeScene("menu");

	engine::Game::instance.run();

	return 0;
}
