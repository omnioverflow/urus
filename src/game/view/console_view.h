#pragma once 

#if !defined(NDEBUG)
# include "game_view.h"

namespace urus
{
	class ConsoleView final : public AnyView
	{
		public:

			static constexpr char* default_title = "ConsoleView";
			ConsoleView() : AnyView(default_title) {}
			ConsoleView(ViewStyle style) : AnyView(default_title, style) {}
			void updateViewPositionAndBounds() const override;
	}; // class ConsoleView
} // namespace urus
#endif // NDEBUG
