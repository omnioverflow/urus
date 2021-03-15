#include "game_view.h"

#include "GL/freeglut.h"

namespace urus
{
	void GameView::updateViewPositionAndBounds() const
	{
		std::lock_guard<std::mutex> lock(mObjectStateMutex);

		glutPositionWindow(mX, mY);
		glutReshapeWindow(mWidth, mHeight);
	}
} // namespace urus