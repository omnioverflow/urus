#pragma once 

#ifndef NDEBUG
#include "game_view.h"

namespace urus
{
	class ConsoleView final : public GameView
	{
		public:
			void updateViewPositionAndBounds() const override;
	}; // class ConsoleView
} // namespace urus
#endif
