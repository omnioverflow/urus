#pragma once

/**
 * mq_math.h a.k.a. macaque math
*/

namespace macaque
{
    static constexpr float MQ_EPSILON = 1.0e-7;

    inline bool isZero(float x)
    {
        return (x < MQ_EPSILON) && (x > -MQ_EPSILON);
    }
} // namespace macaque
