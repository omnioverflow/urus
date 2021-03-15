#pragma once 

#include "any_view.h"

namespace urus
{
	class GameView : public AnyView
	{
		public:

			using AnyView::AnyView;

			virtual void updateViewPositionAndBounds() const override;
	}; // class GameView
} // namespace urus
