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

	game.setGameView(
		std::make_shared<urus::GameView>("Urus", urus::ViewStyle::TOP_RIGHT)
	);
	
#if !defined(NDEBUG)
	game.setConsoleView(
		std::make_shared<urus::ConsoleView>(urus::ViewStyle::BOTTOM_RIGHT)
	);
#endif // NDEBUG

	game.setup(argc, argv);
	game.updateViewPositionAndBounds();

	// Enter game infinite loop
	game.run();
	game.shutdown();
}