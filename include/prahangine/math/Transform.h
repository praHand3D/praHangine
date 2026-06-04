#pragma once
#include "Vec.h"


struct Transform {
    Vec3 position;
    Vec4 rotation;
    Vec3 scale;

    Transform(Vec3 position, Vec4 rotation, Vec3 scale) : position(position), rotation(rotation), scale(scale) {}
    Transform() : position(Vec3(0, 0, 0)), rotation(Vec4(0, 0, 0, 0)), scale(Vec3(1, 1, 1)) {}
};
