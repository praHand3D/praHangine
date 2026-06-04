#pragma once


struct Vec3 {
    float x, y, z;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    Vec3(): x(0), y(0), z(0) {};

    static Vec3 normalize(const Vec3& v);
    static Vec3 cross(const Vec3& v1, const Vec3& v2);
    static float dot(const Vec3& v1, const Vec3& v2);
};

Vec3 operator+(const Vec3 &v1, const Vec3 &v2);
Vec3 operator+(const Vec3 &v1, float value);
Vec3 operator-(const Vec3& v1, const Vec3& v2);
Vec3 operator-(const Vec3 &v1, float value);
Vec3 operator*(const Vec3 &v1, float value);
Vec3 operator/(const Vec3 &v1, float value);


struct Vec4 {
    float x, y, z, w;
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
    Vec4(): x(0), y(0), z(0), w(0) {};
};
