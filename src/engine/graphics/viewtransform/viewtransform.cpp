#include "viewtransform.h"

#include "vec.h"

using namespace urus;

macaque::vec3 ViewTransform::toEyespace(
        macaque::vec3& screenPos, 
        uint32_t screenWidth,
        uint32_t screenHeight)
{
    if (!screenHeight)
        return 
            macaque::vec3{ static_cast<float>(screenPos[0]),
            static_cast<float>(screenPos[1]), 1.0f };
    else 
    {
        const auto radius = static_cast<float>(screenHeight / 2);
        return
            macaque::vec3 { (static_cast<float>(screenPos[0]) - radius) / radius,
            (static_cast<float>(screenPos[1]) - radius) / radius,
            1.0f };
    }
}
