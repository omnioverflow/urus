#if !defined(NDEBUG)

#include "ConsoleView.h"

#include <string>

#if defined(_WIN64)
# include <windows.h>
#endif // _WIN64

namespace urus
{
    const std::string ConsoleView::default_title = "ConsoleView";

    void ConsoleView::updateViewPositionAndBounds() const
    {
        #if defined(_WIN64)
            HWND handleWnd = GetConsoleWindow();
            MoveWindow(handleWnd, mX, mY, mWidth, mHeight, TRUE /* repaint */);
        #endif // _WIN64

        #if defined(__APPLE__)
        // noop
        #endif // __APPLE__
    }
} // namespace urus
#endif // NDEBUG
