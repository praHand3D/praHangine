#include "prahangine/math/Vec.h"

#include <cmath>


Vec3 Vec3::normalize(const Vec3 &v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (len == 0.0f)
        return {0.0f, 0.0f, 0.0f};

    return {v.x / len, v.y / len, v.z / len};
};

Vec3 Vec3::cross(const Vec3 &v1, const Vec3 &v2) {
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
};

float Vec3::dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
};

Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vec3 operator+(const Vec3 &v1, float value) {
    return {v1.x + value, v1.y + value, v1.z + value};
};

Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vec3 operator-(const Vec3 &v1, float value) {
    return {v1.x - value, v1.y - value, v1.z - value};
}

Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

Vec3 operator*(const Vec3 &v1, float value) {
    return {v1.x * value, v1.y * value, v1.z * value};
}

Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}

Vec3 operator/(const Vec3 &v1, float value) {
    return {v1.x / value, v1.y / value, v1.z / value};
}


Vec4 Vec4::multiplyQuaternions(const Vec4 &q1, const Vec4 &q2) {
    return {
        q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
        q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
        q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w,
        q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z
    };
};

