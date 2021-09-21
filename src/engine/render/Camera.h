#pragma once 

#include "mqMath/Mat.h"

using namespace mq;

namespace urus {
    enum class FovType : uint8_t {
        Horizontal = 0,
        Vertical
    };

    enum class Projection : uin8_t {
        Perspective = 0,
        Ortho
    };

    class Camera {
    public:
        /**
         * @brief Viewing transformation matrix generation.
         * The view matrix is the inverse of the camera's transformation.
         * Instead of having to create the camera's transform matrix and then
         * invert it, the lookAt method generates this matrix directly.
         */
        mat4 lookAt(const vec3& origin, const vec3& target, const vec3& up);

        void setProjection(float fov, float aspect, float near, float far);

        mat4 getProjectionMatrix() const;
        mat4 getViewMatrix() const;
    };
} // namespace urus