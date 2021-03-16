#include <memory>

#include "game/game.h"
#include "game/view/views.h"

using namespace urus;

int main(int argc, char* argv[])
{
	auto& game = Game::sharedInstance();

	game.setGameView(std::make_unique<GameView>("Urus", ViewStyle::TOP_RIGHT));

#if !defined(NDEBUG)
	game.setConsoleView(std::make_shared<ConsoleView>(ViewStyle::BOTTOM_RIGHT));
#endif // NDEBUG

	game.setup(argc, argv);
	game.updateViewPositionAndBounds();
	game.logScreenInfo();

	// Enter game infinite loop
	int exitCode = game.run();
	game.shutdown();

	return exitCode;
}