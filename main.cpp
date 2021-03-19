#include <memory>

#include "game/game.h"
#include "game/view/views.h"
#include "engine/graphics/display_config.h"

using namespace urus;

int main(int argc, char* argv[])
{
	DisplayConfig::logScreenInfo();

	auto& game = Game::sharedInstance();
	game.setGameView(std::make_unique<GameView>("Urus"));

#if !defined(NDEBUG)
	game.setConsoleView(std::make_unique<ConsoleView>());
#endif // NDEBUG

	game.createView(argc, argv);
	game.loadResources();
	game.updateViewPositionAndBounds();

	// Enter game infinite loop
	int exitCode = game.run();
	game.shutdown();

	return exitCode;
}