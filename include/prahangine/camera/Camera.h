#pragma once

#include "prahangine/math/Matrix.h"
#include "prahangine/math/Vec.h"


struct Camera {
    Vec3 position;
    Vec3 up;
    Vec3 target;

    Matrix4x4 view{};
    Matrix4x4 projection{};

    Camera(Vec3 position, Vec3 up, Vec3 target) : position(position), up(up), target(target) {}

    void buildViewMatrix();
    void buildProjectionMatrix(float fov, float aspect, float near, float far);
};
