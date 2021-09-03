#pragma once 

#include "AnyView.h"

namespace urus
{
	class GameView : public AnyView
	{
		public:

			explicit GameView(const std::string& title) : GameView(title, default_style) {}
			GameView(const std::string& title, ViewStyle style) : AnyView(title, style) {}

			virtual void updateViewPositionAndBounds() const override;

		private:

			static constexpr ViewStyle default_style = ViewStyle::Top_Right;
	}; // class GameView
} // namespace urus
