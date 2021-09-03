#include <memory>

#include "game/Game.h"
#include "game/view/Views.h"
#include "engine/viewtransform/DisplayConfig.h"

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