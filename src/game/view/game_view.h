#pragma once 

#include <mutex>
#include <string>

namespace urus
{
	enum class WindowPosition : int 
	{
		BOTTOM_LEFT = 0,
		BOTTOM_RIGHT,
		TOP_LEFT,
		TOP_RIGHT,
		FULLSCREEN,
		ANY
	}; // enum WindowPosition

	class Window
	{
		public:
			Window();
			explicit Window(const std::string& title);

			virtual ~Window() {}
			/**
			 * Set window to fullscreen
			 */
			void makeFullscreen();
			/**
			 * Corner snap positioning 
			 * (similar to window snap on Windows OS, e.g. Win + arrow)
			 */
			void snapWindowPosition(WindowPosition position);
			/**
			 * Set custom window width and height            
			 */
			void setWindowBounds(int width, int height);
			/**
			 * Update window position and bounds
			 */
			virtual void updateWindowPositionAndBounds() const;
			/**
			 * Retrieve window's title
			 */
			inline std::string title() const { return mTitle;  }

		protected:

			std::string mTitle;
			int mX, mY, mWidth, mHeight;
			WindowPosition mPosition;
			mutable std::mutex mObjectStateMutex;
	}; // class Window
} // namespace urus
