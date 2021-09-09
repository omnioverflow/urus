#pragma once

#include <stdint.h>

#include "mqMath/Vec.h"

namespace urus
{
	class ViewTransform 
	{
		public:
			// FIXME: screenPos is supposed to be an int vector
			static mq::vec3 toEyespace(mq::vec3& screenPos,
											uint32_t screenWidth,
											uint32_t screenHeight); 
	}; // class ViewTransform
} // namespace urus
