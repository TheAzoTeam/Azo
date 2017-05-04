#include "game.hpp"
#include "game_globals.hpp"

int main(int, char**) {
	engine::Game::instance.SetAttributes(global::game_name,
					     global::window_width,
					     global::window_height,
					     global::frame_rate);



	engine::GameObject player("player_object");
	engine::ImageComponent player_image(player, "sprites/scottpilgrim_multiple.png");
	player.AddComponent(player_image);

	engine::Scene player_scene("player_scene");
	player_scene.AddGameObject(player);

	engine::Game::instance.AddScene(player_scene);

	engine::Game::instance.Run();
	return 0;
}