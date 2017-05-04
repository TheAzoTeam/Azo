#include "game.hpp"
#include "game_globals.hpp"
#include "player_object.hpp"

int main(int, char**) {
	engine::Game game(
		global::game_name,
		global::window_width,
		global::window_heigth);

	PlayerObject player;
	engine::Scene player_scene("player_scene");

	player_scene.AddGameObject(player);

	game.AddScene(player_scene);

	game.Run();
	return 0;
}