/**
     * @file main.cpp
	 * @brief Purpose: Main game Compilation file
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#include "game.hpp"
#include "game_globals.hpp"
#include "level_one.hpp"
#include "menu.hpp"

using namespace Azo;

/**
     * @brief function responsible for calling and compiling the game
     *
     * Why: Because it is responsible for the startup and finalization of the game
	 *
	 * @return Integer with output status.
     */
int main(int, char**) {
	// Setting the game global variables (such as screen size and frame rate) before starting.
	engine::Game::instance.setAttributes(
		global::GAME_NAME,
		global::WINDOWN_WIDTH,
		global::WINDOWN_HEIGHT,
		global::FRAME_RATE);

	// Creating references to the scenes of the game.
	LevelOne level_one("level_one");
	Menu menu("menu");

	// Adding scenes to the map
	engine::Game::instance.addScene(level_one);
	engine::Game::instance.addScene(menu);

	// Changing scene to ' menu '
	engine::Game::instance.changeScene("menu");

	// Running game 
	engine::Game::instance.run();

	return 0;
}
