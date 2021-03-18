#pragma once 

#if !defined(NDEBUG)
# include "game_view.h"

namespace urus
{
	class ConsoleView final : public AnyView
	{
		public:
			
			ConsoleView() : AnyView(default_title) {}
			ConsoleView(ViewStyle style) : AnyView(default_title, style) {}
			void updateViewPositionAndBounds() const override;

		private:
			
			static constexpr char* default_title = "ConsoleView";
	}; // class ConsoleView
} // namespace urus
#endif // NDEBUG
