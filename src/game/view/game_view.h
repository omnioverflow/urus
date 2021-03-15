#pragma once 

#include <mutex>
#include <string>

namespace urus
{
	enum class GameViewStyle : int 
	{
		BOTTOM_LEFT = 0,
		BOTTOM_RIGHT,
		TOP_LEFT,
		TOP_RIGHT,
		FULLSCREEN,
		ANY
	}; // enum GameViewStyle

	class GameView
	{
		public:
			GameView();
			explicit GameView(const std::string& title);

			virtual ~GameView() {}

			/**
			 * Set window to fullscreen
			 */
			void makeFullscreen();

			/**
			 * Corner snap positioning 
			 * (similar to window snap on Windows OS, e.g. Win + arrow)
			 */
			void snapView(GameViewStyle style);

			/**
			 * Set custom window width and height            
			 */
			void setViewBounds(int width, int height);

			/**
			 * Update view's position and bounds
			 */
			virtual void updateViewPositionAndBounds() const;

			/**
			 * Retrieve view's title
			 */
			inline std::string title() const { return mTitle;  }

		protected:

			std::string mTitle;
			int mX, mY, mWidth, mHeight;
			GameViewStyle mStyle;
			mutable std::mutex mObjectStateMutex;
	}; // class GameView
} // namespace urus
