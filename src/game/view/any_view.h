#pragma once

#include <mutex>
#include <string>

namespace urus
{
    enum class ViewStyle : int 
    {
        BOTTOM_LEFT = 0,
        BOTTOM_RIGHT,
        TOP_LEFT,
        TOP_RIGHT,
        FULLSCREEN,
        ANY
    }; // enum ViewStyle

    class AnyView
    {
        public:

            explicit AnyView(const std::string& title);
            AnyView(const std::string& title, ViewStyle style);
            virtual ~AnyView() = default;
            AnyView(const AnyView& other) = default;
            AnyView& operator= (const AnyView& other) = default;
            AnyView(AnyView&& other) = default;
            AnyView& operator= (AnyView&& other) = default;

            /**
            * Set view to fullscreen style.
            */
            void setFullscreen();

            /**
             * Corner snap positioning depending on the style
             * (i.e. top left, top right, bottom left, bottom right)
             * The snap behaviour is similar to window snap on Windows OS, e.g. Win + arrow)
             */
            void snapView(ViewStyle style);

            void setViewBounds(int width, int height);            

            /**
             * Retrieve view's title
             */
            inline std::string title() const;

            virtual void updateViewPositionAndBounds() const = 0;

        protected:

            std::string mTitle;
            int mX;
            int mY;
            int mWidth;
            int mHeight;
            ViewStyle mStyle;
            mutable std::mutex mObjectStateMutex;
    }; // class AnyView

    std::string AnyView::title() const
    {
        return mTitle;
    }
} // namespace urus