#ifndef NDEBUG

#ifdef _WIN64
#include <windows.h>
#endif

#include "console_view.h"

using namespace urus;

void ConsoleView::updateViewPositionAndBounds() const
{
#ifdef _WIN64
    HWND handleWnd = GetConsoleWindow();
    MoveWindow(handleWnd, mX, mY, mWidth, mHeight, TRUE /* repaint */);
#endif
}
#endif // ifndef NDEBUG
