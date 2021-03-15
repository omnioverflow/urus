#ifndef NDEBUG

#ifdef _WIN64
# include <windows.h>
#endif // _WIN64

#include "console_view.h"

namespace urus
{
    void ConsoleView::updateViewPositionAndBounds() const
    {
#ifdef _WIN64
        HWND handleWnd = GetConsoleWindow();
        MoveWindow(handleWnd, mX, mY, mWidth, mHeight, TRUE /* repaint */);
#endif // _WIN64
    }
} // namespace urus
#endif // NDEBUG