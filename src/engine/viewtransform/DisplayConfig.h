#pragma once

namespace urus
{
	/**
	 * A helper class that provides utilities to get configurations 
	 * of the host display
	 */
	class DisplayConfig
	{
		public:
			
			static int getScreenWidthPx();
			static int getScreenHeightPx();
			static void logScreenInfo();
	}; // class DisplayConfig
} // namespace urus
