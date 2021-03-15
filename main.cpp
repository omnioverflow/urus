#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
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

	auto& app = urus::Application::sharedInstance();
	auto gameView = std::make_shared<urus::GameView>(std::string("Core OpenGL 4.3 Example"));
	gameView->snapView(urus::GameViewStyle::TOP_RIGHT);
	app.setGameView(gameView);
#ifndef NDEBUG
	auto consoleView = std::make_shared<urus::ConsoleView>();
	consoleView->snapView(urus::GameViewStyle::BOTTOM_RIGHT);
	app.setConsoleView(consoleView);
#endif

	app.setup(argc, argv);
	app.updateViewPositionAndBounds();

	// Enter game infinite loop
	app.run();
	app.shutdown();
}