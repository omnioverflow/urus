#include <memory>

#include "game/game.h"
#include "game/view/views.h"

int main(int argc, char* argv[])
{
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
	game.logScreenInfo();

	// Enter game infinite loop
	game.run();
	game.shutdown();
}