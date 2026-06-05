#include <cmath>
#include "gtest/gtest.h"
#include "math/Vec.h"


// ---- CONSTRUCTORS ----

TEST(VEC3, DEFAULT_CONSTRUCTOR) {
    Vec3 v;
    EXPECT_FLOAT_EQ(v.x, 0);
    EXPECT_FLOAT_EQ(v.y, 0);
    EXPECT_FLOAT_EQ(v.z, 0);
}

TEST(VEC3, CONSTRUCTOR) {
    Vec3 v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

// ---- OPERATOR + ----

TEST(VEC3_ADD, BASIC) {
    Vec3 result = Vec3(1, 2, 3) + Vec3(4, 5, 6);
    EXPECT_FLOAT_EQ(result.x, 5);
    EXPECT_FLOAT_EQ(result.y, 7);
    EXPECT_FLOAT_EQ(result.z, 9);
}

TEST(VEC3_ADD, ZERO) {
    Vec3 result = Vec3(1, 2, 3) + Vec3(0, 0, 0);
    EXPECT_FLOAT_EQ(result.x, 1);
    EXPECT_FLOAT_EQ(result.y, 2);
    EXPECT_FLOAT_EQ(result.z, 3);
}

TEST(VEC3_ADD, NEGATIVE) {
    Vec3 result = Vec3(1, 2, 3) + Vec3(-1, -2, -3);
    EXPECT_FLOAT_EQ(result.x, 0);
    EXPECT_FLOAT_EQ(result.y, 0);
    EXPECT_FLOAT_EQ(result.z, 0);
}

TEST(VEC3_ADD, FLOAT) {
    Vec3 result = Vec3(1, 2, 3) + 2.0f;
    EXPECT_FLOAT_EQ(result.x, 3);
    EXPECT_FLOAT_EQ(result.y, 4);
    EXPECT_FLOAT_EQ(result.z, 5);
}

TEST(VEC3_ADD, FLOAT_ZERO) {
    Vec3 result = Vec3(1, 2, 3) + 0.0f;
    EXPECT_FLOAT_EQ(result.x, 1);
    EXPECT_FLOAT_EQ(result.y, 2);
    EXPECT_FLOAT_EQ(result.z, 3);
}

TEST(VEC3_ADD, FLOAT_NEGATIVE) {
    Vec3 result = Vec3(1, 2, 3) + (-1.0f);
    EXPECT_FLOAT_EQ(result.x, 0);
    EXPECT_FLOAT_EQ(result.y, 1);
    EXPECT_FLOAT_EQ(result.z, 2);
}

// ---- OPERATOR - ----

TEST(VEC3_SUB, BASIC) {
    Vec3 result = Vec3(4, 5, 6) - Vec3(1, 2, 3);
    EXPECT_FLOAT_EQ(result.x, 3);
    EXPECT_FLOAT_EQ(result.y, 3);
    EXPECT_FLOAT_EQ(result.z, 3);
}

TEST(VEC3_SUB, ZERO) {
    Vec3 result = Vec3(1, 2, 3) - Vec3(0, 0, 0);
    EXPECT_FLOAT_EQ(result.x, 1);
    EXPECT_FLOAT_EQ(result.y, 2);
    EXPECT_FLOAT_EQ(result.z, 3);
}

TEST(VEC3_SUB, SELF) {
    Vec3 v(3, 5, 7);
    Vec3 result = v - v;
    EXPECT_FLOAT_EQ(result.x, 0);
    EXPECT_FLOAT_EQ(result.y, 0);
    EXPECT_FLOAT_EQ(result.z, 0);
}

TEST(VEC3_SUB, FLOAT) {
    Vec3 result = Vec3(4, 5, 6) - 1.0f;
    EXPECT_FLOAT_EQ(result.x, 3);
    EXPECT_FLOAT_EQ(result.y, 4);
    EXPECT_FLOAT_EQ(result.z, 5);
}

TEST(VEC3_SUB, FLOAT_ZERO) {
    Vec3 result = Vec3(1, 2, 3) - 0.0f;
    EXPECT_FLOAT_EQ(result.x, 1);
    EXPECT_FLOAT_EQ(result.y, 2);
    EXPECT_FLOAT_EQ(result.z, 3);
}

// ---- OPERATOR * float ----

TEST(VEC3_MUL, FLOAT) {
    Vec3 result = Vec3(1, 2, 3) * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2);
    EXPECT_FLOAT_EQ(result.y, 4);
    EXPECT_FLOAT_EQ(result.z, 6);
}

TEST(VEC3_MUL, FLOAT_ZERO) {
    Vec3 result = Vec3(1, 2, 3) * 0.0f;
    EXPECT_FLOAT_EQ(result.x, 0);
    EXPECT_FLOAT_EQ(result.y, 0);
    EXPECT_FLOAT_EQ(result.z, 0);
}

TEST(VEC3_MUL, FLOAT_NEGATIVE) {
    Vec3 result = Vec3(1, 2, 3) * (-1.0f);
    EXPECT_FLOAT_EQ(result.x, -1);
    EXPECT_FLOAT_EQ(result.y, -2);
    EXPECT_FLOAT_EQ(result.z, -3);
}


// ---- OPERATOR / float ----

TEST(VEC3_DIV, FLOAT) {
    Vec3 result = Vec3(2, 4, 6) / 2.0f;
    EXPECT_FLOAT_EQ(result.x, 1);
    EXPECT_FLOAT_EQ(result.y, 2);
    EXPECT_FLOAT_EQ(result.z, 3);
}

TEST(VEC3_DIV, FLOAT_ONE) {
    Vec3 result = Vec3(1, 2, 3) / 1.0f;
    EXPECT_FLOAT_EQ(result.x, 1);
    EXPECT_FLOAT_EQ(result.y, 2);
    EXPECT_FLOAT_EQ(result.z, 3);
}

// ---- NORMALIZE ----

TEST(VEC3_NORMALIZE, UNIT_VECTOR) {
    Vec3 v;
    Vec3 result = v.normalize(Vec3(1, 0, 0));
    EXPECT_NEAR(result.x, 1.0f, 1e-5f);
    EXPECT_NEAR(result.y, 0.0f, 1e-5f);
    EXPECT_NEAR(result.z, 0.0f, 1e-5f);
}

TEST(VEC3_NORMALIZE, LENGTH_IS_ONE) {
    Vec3 v;
    Vec3 result = v.normalize(Vec3(1, 2, 3));
    float len = std::sqrt(result.x*result.x + result.y*result.y + result.z*result.z);
    EXPECT_NEAR(len, 1.0f, 1e-5f);
}

TEST(VEC3_NORMALIZE, NEGATIVE) {
    Vec3 v;
    Vec3 result = v.normalize(Vec3(-3, 0, 0));
    EXPECT_NEAR(result.x, -1.0f, 1e-5f);
    EXPECT_NEAR(result.y, 0.0f, 1e-5f);
    EXPECT_NEAR(result.z, 0.0f, 1e-5f);
}

// ---- CROSS ----

TEST(VEC3_CROSS, X_CROSS_Y_IS_Z) {
    Vec3 v;
    Vec3 result = v.cross(Vec3(1, 0, 0), Vec3(0, 1, 0));
    EXPECT_NEAR(result.x, 0.0f, 1e-5f);
    EXPECT_NEAR(result.y, 0.0f, 1e-5f);
    EXPECT_NEAR(result.z, 1.0f, 1e-5f);
}

TEST(VEC3_CROSS, ANTICOMMUTATIVE) {
    Vec3 v;
    Vec3 r1 = v.cross(Vec3(1, 0, 0), Vec3(0, 1, 0));
    Vec3 r2 = v.cross(Vec3(0, 1, 0), Vec3(1, 0, 0));
    EXPECT_NEAR(r1.x, -r2.x, 1e-5f);
    EXPECT_NEAR(r1.y, -r2.y, 1e-5f);
    EXPECT_NEAR(r1.z, -r2.z, 1e-5f);
}

TEST(VEC3_CROSS, PARALLEL_IS_ZERO) {
    Vec3 v;
    Vec3 result = v.cross(Vec3(1, 0, 0), Vec3(2, 0, 0));
    EXPECT_NEAR(result.x, 0.0f, 1e-5f);
    EXPECT_NEAR(result.y, 0.0f, 1e-5f);
    EXPECT_NEAR(result.z, 0.0f, 1e-5f);
}

// ---- DOT ----

TEST(VEC3_DOT, PERPENDICULAR_IS_ZERO) {
    Vec3 v;
    float result = v.dot(Vec3(1, 0, 0), Vec3(0, 1, 0));
    EXPECT_NEAR(result, 0.0f, 1e-5f);
}

TEST(VEC3_DOT, PARALLEL) {
    Vec3 v;
    float result = v.dot(Vec3(1, 0, 0), Vec3(1, 0, 0));
    EXPECT_NEAR(result, 1.0f, 1e-5f);
}

TEST(VEC3_DOT, BASIC) {
    Vec3 v;
    float result = v.dot(Vec3(1, 2, 3), Vec3(4, 5, 6));
    EXPECT_NEAR(result, 32.0f, 1e-5f);
}

TEST(VEC3_DOT, ANTIPARALLEL) {
    Vec3 v;
    float result = v.dot(Vec3(1, 0, 0), Vec3(-1, 0, 0));
    EXPECT_NEAR(result, -1.0f, 1e-5f);
}