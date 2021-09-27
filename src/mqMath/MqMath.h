#pragma once

/**
 * mq_math.h a.k.a. mq math
*/

namespace mq
{
    namespace internal
    {
        constexpr float MQ_EPSILON = 1.0e-7;
        constexpr float MQ_PI = 3.14159265359f;
        constexpr float MQ_RADIANS_PER_DEGREE = MQ_PI / 180.f;
    }
    
    static inline bool isZero(float x) {
        return (x < internal::MQ_EPSILON) && (x > -internal::MQ_EPSILON);
    }
} // namespace mq
