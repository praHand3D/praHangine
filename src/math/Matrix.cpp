#include "prahangine/math/Matrix.h"

Matrix4x4 multipy(Matrix4x4 m1, Matrix4x4 m2) {
    Matrix4x4 result{};

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            for (int k = 0; k < 4; k++)
                result.data[r][c] += m1.data[r][k] * m2.data[k][c];

    return result;
}

Matrix4x4 buildModelMatrix(const Transform &transform) {
    Matrix4x4 translation = buildTranslationMatrix(transform.position);
    Matrix4x4 rotation    = buildRotationMatrix(transform.rotation);
    Matrix4x4 scale       = buildScaleMatrix(transform.scale);
    return multipy(translation, multipy(rotation, scale));
}

Matrix4x4 buildTranslationMatrix(const Vec3 &position) {
    return Matrix4x4{{
        {1, 0, 0, position.x},
        {0, 1, 0, position.y},
        {0, 0, 1, position.z},
        {0, 0, 0, 1}
    }};
}

Matrix4x4 buildRotationMatrix(const Vec4 &rotation) {
    float x = rotation.x;
    float y = rotation.y;
    float z = rotation.z;
    float w = rotation.w;

    return Matrix4x4{{
        {1-2*(y*y+z*z),   2*(x*y-w*z),   2*(x*z+w*y),  0},
        {  2*(x*y+w*z), 1-2*(x*x+z*z),   2*(y*z-w*x),  0},
        {  2*(x*z-w*y),   2*(y*z+w*x), 1-2*(x*x+y*y),  0},
        {     0,              0,              0,       1}
    }};
}

Matrix4x4 buildScaleMatrix(const Vec3 &scale) {
    return Matrix4x4{{
        {scale.x, 0, 0, 0},
        {0, scale.y, 0, 0},
        {0, 0, scale.z, 0},
        {0, 0, 0, 1}
    }};
}
