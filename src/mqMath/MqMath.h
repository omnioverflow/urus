#pragma once

/**
 * mq_math.h a.k.a. macaque math
*/

namespace macaque
{
    namespace internal
    {
        constexpr float MQ_EPSILON = 1.0e-7;
    }
    
    inline bool isZero(float x)
    {
        return (x < internal::MQ_EPSILON) && (x > -internal::MQ_EPSILON);
    }
} // namespace macaque
