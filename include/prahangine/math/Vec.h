#pragma once


struct Vec3 {
    float x, y, z;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    Vec3(): x(0), y(0), z(0) {};
};

struct Vec4 {
    float x, y, z, w;
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
    Vec4(): x(0), y(0), z(0), w(0) {};
};
