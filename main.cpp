#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "engine/graphics/display_config.h"
#include "game/game.h"
#include "game/view/views.h"

int main(int argc, char* argv[])
{
	std::cout << urus::DisplayConfig::getScreenWidth() << ", ";
	std::cout << urus::DisplayConfig::getScreenHeight() << std::endl;

	auto& game = urus::Game::sharedInstance();
	
	auto gameView = std::make_shared<urus::GameView>("Core OpenGL 4.3 Example");
	gameView->snapView(urus::ViewStyle::TOP_RIGHT);
	game.setGameView(gameView);
	
#ifndef NDEBUG
	auto consoleView = std::make_shared<urus::ConsoleView>();
	consoleView->snapView(urus::ViewStyle::BOTTOM_RIGHT);
	game.setConsoleView(consoleView);
#endif

	game.setup(argc, argv);
	game.updateViewPositionAndBounds();

	// Enter game infinite loop
	game.run();
	game.shutdown();
}