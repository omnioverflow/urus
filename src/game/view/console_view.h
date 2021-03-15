#pragma once 

#ifndef NDEBUG
#include "game_view.h"

namespace urus
{
	class ConsoleView final : public AnyView
	{
		public:

			ConsoleView() : AnyView("ConsoleView") {}
			void updateViewPositionAndBounds() const override;
	}; // class ConsoleView
} // namespace urus
#endif
