#pragma once

#include <vector>

#include "prahangine/math/Transform.h"
#include "prahangine/math/Vec.h"


struct Header {
    uint8_t magic[4];
    uint8_t version;
    uint8_t mesh_count;
    uint8_t object_count;
    uint8_t animation_count;

    Header(): mesh_count(0), object_count(0), animation_count(0) {};
};

struct Vertex {
    Vec3 position;

    Vertex(float x, float y, float z) : position({x, y, z}) {};
    Vertex() : Vertex(0, 0, 0) {};
};

struct Index {
    uint16_t vertexes_index[3];

    Index(uint8_t v1, uint8_t v2, uint8_t v3): vertexes_index{v1, v2, v3} {};
    Index() : Index(0, 0, 0) {};
};

struct Mesh {
    uint8_t id;
    std::vector<Vertex> vertexes;
    std::vector<Index> indices;
};

struct Object {
    uint8_t id;
    uint8_t mesh_ref;
    Transform transform;

    Object() {};
    Object(uint8_t id, uint8_t mesh_ref, Transform transform) : id(id), mesh_ref(mesh_ref), transform(transform) {};
};

struct Keyframe {
    Transform transform;
};

struct Animation {
    uint8_t id;
    uint8_t object_ref;
    uint8_t fps;
    std::vector<Keyframe> keyframes;
};
