#include "game_view.h"

#include <cassert>

#include "engine/graphics/display_config.h"
#include "GL/freeglut.h"

using namespace urus;

GameView::GameView()
: GameView(std::string(""))
{
}

GameView::GameView(const std::string& title)
: mTitle(title)
, mX(0)
, mY(0)
, mWidth(DisplayConfig::getScreenWidth())
, mHeight(DisplayConfig::getScreenHeight())
, mStyle(GameViewStyle::FULLSCREEN)
{
}

void GameView::makeFullscreen() 
{
	std::lock_guard<std::mutex> lock(mObjectStateMutex);

	mX = 0, mY = 0;
	mWidth = DisplayConfig::getScreenWidth();
	mHeight = DisplayConfig::getScreenHeight();
	mStyle = GameViewStyle::FULLSCREEN;
}

void GameView::snapView(GameViewStyle style)
{
	const auto screenWidth = DisplayConfig::getScreenWidth();
	const auto screenHeight = DisplayConfig::getScreenHeight();
	auto widthToApply = screenWidth / 2;
	auto heightToApply = screenHeight / 2;

	{
		std::lock_guard<std::mutex> lock(mObjectStateMutex);

		switch (style)
		{
			case GameViewStyle::BOTTOM_LEFT:
				mX = 0;
				mY = 1 + heightToApply;
				mWidth = screenWidth / 2;
				mHeight = screenHeight - mY;           
				break;
			case GameViewStyle::BOTTOM_RIGHT:
				mX = 1 + widthToApply;
				mY  = 1 + heightToApply;
				mWidth = screenWidth - mX;
				mHeight = screenHeight - mY;
				break;
			case GameViewStyle::TOP_LEFT:
				mX = 0;
				mY = 0;
				mWidth = widthToApply;
				mHeight = heightToApply;
				break;
			case GameViewStyle::TOP_RIGHT:
				mX = 1 + widthToApply;
				mY = 0;
				mWidth = screenWidth - mX;
				mHeight = heightToApply;
				break;
			default:
				assert(false);
				break;
		}

		mStyle = style;
	}
}

void GameView::setViewBounds(int width, int height)
{
	if (width < 0 || height < 0)
		assert(false);
	else
	{
		std::lock_guard<std::mutex> lock(mObjectStateMutex);

		mWidth = width;
		mHeight = height;
		mStyle = GameViewStyle::ANY;
	}
}

void GameView::updateViewPositionAndBounds() const
{
	std::lock_guard<std::mutex> lock(mObjectStateMutex);

	glutPositionWindow(mX, mY);
	glutReshapeWindow(mWidth, mHeight);
}
