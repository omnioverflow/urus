#include "any_view.h"

#include <cassert>

#include "engine/graphics/display_config.h"
#include "GL/freeglut.h"

namespace urus
{
    AnyView::AnyView(const std::string& title)
    : mTitle(title)
    , mX(0)
    , mY(0)
    , mWidth(DisplayConfig::getScreenWidthPx())
    , mHeight(DisplayConfig::getScreenHeightPx())
    , mStyle(ViewStyle::Fullscreen) {}

    AnyView::AnyView(const std::string& title, ViewStyle style)
    : AnyView(title)
    {
        snapView(style);
    }

    void AnyView::setFullscreen() 
    {
        std::lock_guard<std::mutex> lock(mObjectStateMutex);

        mX = 0, mY = 0;
        mWidth = DisplayConfig::getScreenWidthPx();
        mHeight = DisplayConfig::getScreenWidthPx();
        mStyle = ViewStyle::Fullscreen;
    }

    void AnyView::snapView(ViewStyle style)
    {
        const auto screenWidth = DisplayConfig::getScreenWidthPx();
        const auto screenHeight = DisplayConfig::getScreenHeightPx();
        auto widthToApply = screenWidth / 2;
        auto heightToApply = screenHeight / 2;

        std::lock_guard<std::mutex> lock(mObjectStateMutex);

        switch (style)
        {
            case ViewStyle::Bottom_Left:
            {
                mX = 0;
                mY = 1 + heightToApply;
                mWidth = screenWidth / 2;
                mHeight = screenHeight - mY;           
                break;
            }
            case ViewStyle::Bottom_Right:
            {
                mX = 1 + widthToApply;
                mY  = 1 + heightToApply;
                mWidth = screenWidth - mX;
                mHeight = screenHeight - mY;
                break;
            }
            case ViewStyle::Top_Left:
            {
                mX = 0;
                mY = 0;
                mWidth = widthToApply;
                mHeight = heightToApply;
                break;
            }
            case ViewStyle::Top_Right:
            {
                mX = 1 + widthToApply;
                mY = 0;
                mWidth = screenWidth - mX;
                mHeight = heightToApply;
                break;
            }
            default:
            {
                assert(false);
                break;
            }
        }

        mStyle = style;
}

void AnyView::setViewBounds(int width, int height)
{
    if (width < 0 || height < 0)
        assert(false);
    else
    {
        std::lock_guard<std::mutex> lock(mObjectStateMutex);

        mWidth = width;
        mHeight = height;
        mStyle = ViewStyle::Any;
    }
}
} // namespace urus