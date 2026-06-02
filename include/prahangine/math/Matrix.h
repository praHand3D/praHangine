#pragma once
#include "Transform.h"
#include "Vec.h"

struct Matrix4x4 {
    float data[4][4];
};

Matrix4x4 multipy(Matrix4x4 m1, Matrix4x4 m2);

Matrix4x4 buildModelMatrix(const Transform& transform);

Matrix4x4 buildTranslationMatrix(const Vec3& position);
Matrix4x4 buildRotationMatrix(const Vec4& rotation);
Matrix4x4 buildScaleMatrix(const Vec3& scale);
