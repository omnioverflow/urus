#pragma once 

#if !defined(NDEBUG)
# include "game_view.h"

namespace urus
{
	class ConsoleView final : public AnyView
	{
		public:
			
			ConsoleView() : AnyView(default_title, default_style) {}
			ConsoleView(ViewStyle style) : AnyView(default_title, style) {}
			void updateViewPositionAndBounds() const override;

		private:
			
			static const ViewStyle default_style = ViewStyle::Bottom_Right;
			static const std::string default_title;
	}; // class ConsoleView
} // namespace urus
#endif // NDEBUG
