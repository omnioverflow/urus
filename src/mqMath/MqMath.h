#pragma once

/**
 * mq_math.h a.k.a. mq math
*/

namespace mq
{
    namespace internal
    {
        constexpr float MQ_EPSILON = 1.0e-7;
    }
    
    inline bool isZero(float x)
    {
        return (x < internal::MQ_EPSILON) && (x > -internal::MQ_EPSILON);
    }
} // namespace mq
