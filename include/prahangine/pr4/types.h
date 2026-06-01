#pragma once

#include <vector>
#include "prahangine/math/Vec.h"

struct Header {
    uint8_t magic[4];
    uint8_t version;
    uint8_t mesh_count;
    uint8_t object_count;
    uint8_t animation_count;
};

struct Vertex {
    Vec3 position;
};

struct Index {
    uint16_t vertexes_index[3];
};

struct Mesh {
    uint8_t id;
    std::vector<Vertex> vertexes;
    std::vector<Index> indices;
};

struct Object {
    uint8_t id;
    uint8_t mesh_ref;
    Vec3 position;
    Vec4 rotation;
    Vec3 scale;
};

struct Keyframe {
    Vec3 position;
    Vec4 rotation;
    Vec3 scale;
};

struct Animation {
    uint8_t id;
    uint8_t object_ref;
    uint8_t fps;
    std::vector<Keyframe> keyframes;
};
