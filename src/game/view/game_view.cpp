#include "game_view.h"

#include <cassert>

#include "engine/graphics/display_config.h"
#include "GL/freeglut.h"

using namespace urus;

Window::Window()
: Window(std::string(""))
{
}

Window::Window(const std::string& title)
: mTitle(title)
, mX(0)
, mY(0)
, mWidth(DisplayConfig::getScreenWidth())
, mHeight(DisplayConfig::getScreenHeight())
, mPosition(WindowPosition::FULLSCREEN)
{
}

void Window::makeFullscreen() 
{
	std::lock_guard<std::mutex> lock(mObjectStateMutex);

	mX = 0, mY = 0;
	mWidth = DisplayConfig::getScreenWidth();
	mHeight = DisplayConfig::getScreenHeight();
	mPosition = WindowPosition::FULLSCREEN;
}

void Window::snapWindowPosition(WindowPosition position)
{
	const auto screenWidth = DisplayConfig::getScreenWidth();
	const auto screenHeight = DisplayConfig::getScreenHeight();
	auto widthToApply = screenWidth / 2;
	auto heightToApply = screenHeight / 2;

	{
		std::lock_guard<std::mutex> lock(mObjectStateMutex);

		switch (position)
		{
			case WindowPosition::BOTTOM_LEFT:
				mX = 0;
				mY = 1 + heightToApply;
				mWidth = screenWidth / 2;
				mHeight = screenHeight - mY;           
				break;
			case WindowPosition::BOTTOM_RIGHT:
				mX = 1 + widthToApply;
				mY  = 1 + heightToApply;
				mWidth = screenWidth - mX;
				mHeight = screenHeight - mY;
				break;
			case WindowPosition::TOP_LEFT:
				mX = 0;
				mY = 0;
				mWidth = widthToApply;
				mHeight = heightToApply;
				break;
			case WindowPosition::TOP_RIGHT:
				mX = 1 + widthToApply;
				mY = 0;
				mWidth = screenWidth - mX;
				mHeight = heightToApply;
				break;
			default:
				assert(false);
				break;
		}

		mPosition = position;
	}
}

void Window::setWindowBounds(int width, int height)
{
	if (width < 0 || height < 0)
		assert(false);
	else
	{
		std::lock_guard<std::mutex> lock(mObjectStateMutex);

		mWidth = width;
		mHeight = height;
		mPosition = WindowPosition::ANY;
	}
}

void Window::updateWindowPositionAndBounds() const
{
	std::lock_guard<std::mutex> lock(mObjectStateMutex);

	glutPositionWindow(mX, mY);
	glutReshapeWindow(mWidth, mHeight);
}
