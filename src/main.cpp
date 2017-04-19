#include "game.hpp"
#include "game_globals.hpp"

int main(int, char**) {
	engine::Game game(
		global::game_name,
		global::window_width,
		global::window_heigth);

	game.Run();
	return 0;
}