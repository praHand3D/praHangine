#include "gtest/gtest.h"
#include "prahangine/math/Matrix.h"

// ---- TRANSLATION ----

TEST(MATRIX_TRANSLATION, IDENTITY_POSITION) {
    Vec3 pos = {0, 0, 0};
    Matrix4x4 m = buildTranslationMatrix(pos);
    EXPECT_FLOAT_EQ(m.data[0][3], 0);
    EXPECT_FLOAT_EQ(m.data[1][3], 0);
    EXPECT_FLOAT_EQ(m.data[2][3], 0);
    EXPECT_FLOAT_EQ(m.data[3][3], 1);
}

TEST(MATRIX_TRANSLATION, CORRECT_VALUES) {
    Vec3 pos = {1.0f, 2.0f, 3.0f};
    Matrix4x4 m = buildTranslationMatrix(pos);
    EXPECT_FLOAT_EQ(m.data[0][3], 1.0f);
    EXPECT_FLOAT_EQ(m.data[1][3], 2.0f);
    EXPECT_FLOAT_EQ(m.data[2][3], 3.0f);
}

TEST(MATRIX_TRANSLATION, DIAGONAL_IS_ONE) {
    Vec3 pos = {5.0f, 5.0f, 5.0f};
    Matrix4x4 m = buildTranslationMatrix(pos);
    EXPECT_FLOAT_EQ(m.data[0][0], 1);
    EXPECT_FLOAT_EQ(m.data[1][1], 1);
    EXPECT_FLOAT_EQ(m.data[2][2], 1);
    EXPECT_FLOAT_EQ(m.data[3][3], 1);
}

TEST(MATRIX_TRANSLATION, NEGATIVE_VALUES) {
    Vec3 pos = {-3.0f, -7.0f, -1.5f};
    Matrix4x4 m = buildTranslationMatrix(pos);
    EXPECT_FLOAT_EQ(m.data[0][3], -3.0f);
    EXPECT_FLOAT_EQ(m.data[1][3], -7.0f);
    EXPECT_FLOAT_EQ(m.data[2][3], -1.5f);
}

// ---- SCALE ----

TEST(MATRIX_SCALE, IDENTITY_SCALE) {
    Vec3 scale = {1, 1, 1};
    Matrix4x4 m = buildScaleMatrix(scale);
    EXPECT_FLOAT_EQ(m.data[0][0], 1);
    EXPECT_FLOAT_EQ(m.data[1][1], 1);
    EXPECT_FLOAT_EQ(m.data[2][2], 1);
    EXPECT_FLOAT_EQ(m.data[3][3], 1);
}

TEST(MATRIX_SCALE, CORRECT_VALUES) {
    Vec3 scale = {2.0f, 3.0f, 4.0f};
    Matrix4x4 m = buildScaleMatrix(scale);
    EXPECT_FLOAT_EQ(m.data[0][0], 2.0f);
    EXPECT_FLOAT_EQ(m.data[1][1], 3.0f);
    EXPECT_FLOAT_EQ(m.data[2][2], 4.0f);
}

TEST(MATRIX_SCALE, OFF_DIAGONAL_IS_ZERO) {
    Vec3 scale = {2.0f, 3.0f, 4.0f};
    Matrix4x4 m = buildScaleMatrix(scale);
    EXPECT_FLOAT_EQ(m.data[0][1], 0);
    EXPECT_FLOAT_EQ(m.data[0][2], 0);
    EXPECT_FLOAT_EQ(m.data[1][0], 0);
    EXPECT_FLOAT_EQ(m.data[2][0], 0);
}

// ---- ROTATION ----

TEST(MATRIX_ROTATION, IDENTITY_QUATERNION) {
    // identity quaternion = no rotation
    Vec4 q = {0, 0, 0, 1};
    Matrix4x4 m = buildRotationMatrix(q);
    EXPECT_FLOAT_EQ(m.data[0][0], 1);
    EXPECT_FLOAT_EQ(m.data[1][1], 1);
    EXPECT_FLOAT_EQ(m.data[2][2], 1);
    EXPECT_FLOAT_EQ(m.data[3][3], 1);
    EXPECT_FLOAT_EQ(m.data[0][1], 0);
    EXPECT_FLOAT_EQ(m.data[0][2], 0);
}

TEST(MATRIX_ROTATION, LAST_ROW_IS_ZERO_ZERO_ZERO_ONE) {
    Vec4 q = {0, 0, 0, 1};
    Matrix4x4 m = buildRotationMatrix(q);
    EXPECT_FLOAT_EQ(m.data[3][0], 0);
    EXPECT_FLOAT_EQ(m.data[3][1], 0);
    EXPECT_FLOAT_EQ(m.data[3][2], 0);
    EXPECT_FLOAT_EQ(m.data[3][3], 1);
}

TEST(MATRIX_ROTATION, 180_DEGREES_AROUND_Y) {
    // 180 deg around Y: x=-1, z=-1 diagonal
    Vec4 q = {0, 1, 0, 0};
    Matrix4x4 m = buildRotationMatrix(q);
    EXPECT_NEAR(m.data[0][0], -1.0f, 1e-5f);
    EXPECT_NEAR(m.data[2][2], -1.0f, 1e-5f);
    EXPECT_NEAR(m.data[1][1],  1.0f, 1e-5f);
}

// ---- MULTIPLY ----

TEST(MATRIX_MULTIPLY, IDENTITY_TIMES_IDENTITY) {
    Matrix4x4 identity = {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    Matrix4x4 result = multiply(identity, identity);
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            EXPECT_FLOAT_EQ(result.data[r][c], identity.data[r][c]);
}

TEST(MATRIX_MULTIPLY, TRANSLATION_TIMES_IDENTITY) {
    Vec3 pos = {1.0f, 2.0f, 3.0f};
    Matrix4x4 t = buildTranslationMatrix(pos);
    Matrix4x4 identity = {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    Matrix4x4 result = multiply(t, identity);
    EXPECT_FLOAT_EQ(result.data[0][3], 1.0f);
    EXPECT_FLOAT_EQ(result.data[1][3], 2.0f);
    EXPECT_FLOAT_EQ(result.data[2][3], 3.0f);
}

// ---- BUILD MODEL MATRIX ----

TEST(MATRIX_MODEL, IDENTITY_TRANSFORM) {
    Transform t;
    t.position = {0, 0, 0};
    t.rotation = {0, 0, 0, 1};
    t.scale    = {1, 1, 1};

    Matrix4x4 m = buildModelMatrix(t);
    EXPECT_NEAR(m.data[0][0], 1.0f, 1e-5f);
    EXPECT_NEAR(m.data[1][1], 1.0f, 1e-5f);
    EXPECT_NEAR(m.data[2][2], 1.0f, 1e-5f);
    EXPECT_NEAR(m.data[3][3], 1.0f, 1e-5f);
    EXPECT_NEAR(m.data[0][3], 0.0f, 1e-5f);
    EXPECT_NEAR(m.data[1][3], 0.0f, 1e-5f);
    EXPECT_NEAR(m.data[2][3], 0.0f, 1e-5f);
}

TEST(MATRIX_MODEL, TRANSLATION_ONLY) {
    Transform t;
    t.position = {4.0f, 5.0f, 6.0f};
    t.rotation = {0, 0, 0, 1};
    t.scale    = {1, 1, 1};

    Matrix4x4 m = buildModelMatrix(t);
    EXPECT_NEAR(m.data[0][3], 4.0f, 1e-5f);
    EXPECT_NEAR(m.data[1][3], 5.0f, 1e-5f);
    EXPECT_NEAR(m.data[2][3], 6.0f, 1e-5f);
}

TEST(MATRIX_MODEL, SCALE_ONLY) {
    Transform t;
    t.position = {0, 0, 0};
    t.rotation = {0, 0, 0, 1};
    t.scale    = {2.0f, 3.0f, 4.0f};

    Matrix4x4 m = buildModelMatrix(t);
    EXPECT_NEAR(m.data[0][0], 2.0f, 1e-5f);
    EXPECT_NEAR(m.data[1][1], 3.0f, 1e-5f);
    EXPECT_NEAR(m.data[2][2], 4.0f, 1e-5f);
}

TEST(VEC4_QUATERNION_MULTIPLY, IDENTITY_TIMES_IDENTITY) {
    Vec4 identity = {0, 0, 0, 1};
    Vec4 result = Vec4::multiplyQuaternions(identity, identity);
    EXPECT_NEAR(result.x, 0.0f, 1e-5f);
    EXPECT_NEAR(result.y, 0.0f, 1e-5f);
    EXPECT_NEAR(result.z, 0.0f, 1e-5f);
    EXPECT_NEAR(result.w, 1.0f, 1e-5f);
}

TEST(VEC4_QUATERNION_MULTIPLY, IDENTITY_TIMES_ANY) {
    Vec4 identity = {0, 0, 0, 1};
    Vec4 q = {0.5f, 0.5f, 0.5f, 0.5f};
    Vec4 result = Vec4::multiplyQuaternions(identity, q);
    EXPECT_NEAR(result.x, q.x, 1e-5f);
    EXPECT_NEAR(result.y, q.y, 1e-5f);
    EXPECT_NEAR(result.z, q.z, 1e-5f);
    EXPECT_NEAR(result.w, q.w, 1e-5f);
}

TEST(VEC4_QUATERNION_MULTIPLY, ANY_TIMES_IDENTITY) {
    Vec4 identity = {0, 0, 0, 1};
    Vec4 q = {0.5f, 0.5f, 0.5f, 0.5f};
    Vec4 result = Vec4::multiplyQuaternions(q, identity);
    EXPECT_NEAR(result.x, q.x, 1e-5f);
    EXPECT_NEAR(result.y, q.y, 1e-5f);
    EXPECT_NEAR(result.z, q.z, 1e-5f);
    EXPECT_NEAR(result.w, q.w, 1e-5f);
}

TEST(VEC4_QUATERNION_MULTIPLY, 180_DEG_Y_TWICE_IS_IDENTITY) {
    // 180 deg around Y = (0, 1, 0, 0)
    Vec4 q = {0, 1, 0, 0};
    Vec4 result = Vec4::multiplyQuaternions(q, q);
    EXPECT_NEAR(result.x, 0.0f, 1e-5f);
    EXPECT_NEAR(result.y, 0.0f, 1e-5f);
    EXPECT_NEAR(result.z, 0.0f, 1e-5f);
    EXPECT_NEAR(std::abs(result.w), 1.0f, 1e-5f);
}

TEST(VEC4_QUATERNION_MULTIPLY, NOT_COMMUTATIVE) {
    Vec4 q1 = {1, 0, 0, 0};
    Vec4 q2 = {0, 1, 0, 0};
    Vec4 r1 = Vec4::multiplyQuaternions(q1, q2);
    Vec4 r2 = Vec4::multiplyQuaternions(q2, q1);
    // q1*q2 != q2*q1 for non-identity quaternions
    bool different = std::abs(r1.x - r2.x) > 1e-5f ||
                     std::abs(r1.y - r2.y) > 1e-5f ||
                     std::abs(r1.z - r2.z) > 1e-5f ||
                     std::abs(r1.w - r2.w) > 1e-5f;
    EXPECT_TRUE(different);
}
