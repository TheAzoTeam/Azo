#include "game.hpp"
#include "game_globals.hpp"
#include "player_scene.hpp"

int main(int, char**) {
	engine::Game game(
		global::game_name,
		global::window_width,
		global::window_heigth);

	PlayerScene player_scene;

	game.AddScene(player_scene);

	game.Run();
	return 0;
}