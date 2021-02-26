#pragma once

#include <stdint.h>

#include "macaque/vec.h"

namespace urus
{
	class ViewTransform 
	{
		public:
			// FIXME: screenPos is supposed to be an int vector
			static macaque::vec3 toEyespace(macaque::vec3& screenPos,
											uint32_t screenWidth,
											uint32_t screenHeight); 
	}; // class ViewTransform
} // namespace urus
