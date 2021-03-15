#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "application/application.h"
#include "application/viewer.h"
#include "engine/graphics/display_config.h"
#include "engine/graphics/shader.h"
#include "engine/window/window.h"

#ifndef NDEBUG
#include "engine/window/console.h"
#endif


int main(int argc, char* argv[])
{
	std::cout << urus::DisplayConfig::getScreenWidth() << ", ";
	std::cout << urus::DisplayConfig::getScreenHeight() << std::endl;

	auto& app = urus::Application::sharedInstance();
	auto window = std::make_shared<urus::Window>(std::string("Core OpenGL 4.3 Example"));
	window->snapWindowPosition(urus::WindowPosition::TOP_RIGHT);
	app.setWindow(window);
#ifndef NDEBUG
	auto console = std::make_shared<urus::Console>();
	console->snapWindowPosition(urus::WindowPosition::BOTTOM_RIGHT);
	app.setConsole(console);
#endif

	app.setup(argc, argv);
	app.updateWindowPositionAndBounds();

	// Enter game infinite loop
	app.run();
	app.shutdown();
}