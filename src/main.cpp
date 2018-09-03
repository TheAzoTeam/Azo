#include "game.hpp"
#include "game_globals.hpp"
#include "level_one.hpp"
#include "menu.hpp"

using namespace Azo;

int main(int, char**) {
	// Get the Primary Data for create the game and transfer to SDL do this.
	engine::Game::instance.SetAttributes(
		global::gameName,
		global::windowWidth,
		global::windowHeight,
		global::frame_rate);

	LevelOne level_one("level_one");
	Menu menu("menu");

	engine::Game::instance.AddScene(level_one);
	engine::Game::instance.AddScene(menu);

	engine::Game::instance.ChangeScene("menu");

	engine::Game::instance.Run();

	return 0;
}
