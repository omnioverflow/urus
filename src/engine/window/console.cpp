#ifndef NDEBUG

#ifdef _WIN64
#include <windows.h>
#endif

#include "console.h"

using namespace urus;

void Console::updateWindowPositionAndBounds() const
{
#ifdef _WIN64
    HWND handleWnd = GetConsoleWindow();
    MoveWindow(handleWnd, mX, mY, mWidth, mHeight, TRUE /* repaint */);
#endif
}
#endif // ifndef NDEBUG
