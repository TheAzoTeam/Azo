#include "game.hpp"
#include "game_globals.hpp"


int main(int, char**) {
	engine::Game::instance.SetAttributes(
						 global::game_name,
					     global::window_width,
					     global::window_height,
					     global::frame_rate);

	engine::GameObject player("player_object");

	engine::Animation player_image(player,   // Game Object
			       "sprites/scottpilgrim_multiple.png",   // Imagem Path
			       1200.0f,   // Animation Time
			       2,   // Sprite Rows
			       8,   // Sprite Colums
			       0,   // Start Frame
			       7);   // End Frame

	player.AddComponent(player_image);

	engine::Scene player_scene("player_scene");
	player_scene.AddGameObject(player);

	engine::Game::instance.AddScene(player_scene);

	engine::Game::instance.Run();
	return 0;
}
