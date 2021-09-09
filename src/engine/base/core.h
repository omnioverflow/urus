#pragma once

#include <cfloat>
#include <cmath>

namespace mq
{
	inline bool equalsToZero(float x) { return fabs(x) < FLT_EPSILON; }
	inline bool equals(float x, float y) { return fabs(x - y) < FLT_EPSILON; }
} // namespace walnut,
