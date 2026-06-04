#include <cmath>

#include "prahangine/camera/Camera.h"


void Camera::buildViewMatrix() {
    Vec3 forward = Vec3::normalize(target-position);
    Vec3 right = Vec3::normalize(Vec3::cross(forward, up));
    Vec3 up_corrected = Vec3::cross(right, forward);

    view = Matrix4x4{{
        {right.x, right.y, right.z, -Vec3::dot(right, position)},
        {up_corrected.x, up_corrected.y, up_corrected.z, -Vec3::dot(up_corrected, position)},
        {-forward.x, -forward.y, -forward.z, Vec3::dot(forward, position)},
        {0, 0, 0, 1}
    }};
}

void Camera::buildProjectionMatrix(float fov, float aspect, float near, float far) {
    float tanHalfFOV = std::tan(fov / 2);

    projection = Matrix4x4{{
        {1.0f / (aspect * tanHalfFOV), 0, 0, 0},
        {0, 1.0f / tanHalfFOV, 0, 0},
        {0, 0, -(far + near) / (far - near), -(2.0f * far * near) / (far - near)},
        {0, 0, -1, 0}
    }};
}
