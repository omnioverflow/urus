#include "Camera.h"

namespace urus {
    mat4 Camera::lookAt(const vec3& origin, const vec3& target, const vec3& up) {
        auto forward = normalize(origin - target);
        auto side = normalize(cross(up, forward));
        auto up = normalize(cross(forward, side));
        auto row3 = vec4(0.f, 0.f, 0.f, 1.f);
        auto viewMat = mat4(vec4(u, 1.f), vec4(v, 1.f), vec4(n, 1.f), row3);
        return viewMat * translate(-origin);
    }  
};