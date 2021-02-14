#pragma once 

#ifndef NDEBUG
#include "window.h"

namespace urus
{
	class Console final : public Window
	{
		public:
			void updateWindowPositionAndBounds() const override;
	}; // class Console
} // namespace urus
#endif
