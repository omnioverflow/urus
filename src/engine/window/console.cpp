#ifndef NDEBUG
#include <windows.h>

#include "console.h"

using namespace urus;

void Console::updateWindowPositionAndBounds() const
{
#ifdef _WIN64
	HWND handleWnd = GetConsoleWindow();
	MoveWindow(handleWnd, mX, mY, mWidth, mHeight, TRUE /* repaint */);
#endif
}
#endif
