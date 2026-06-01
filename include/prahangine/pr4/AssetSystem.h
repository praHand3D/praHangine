#pragma once

#include <vector>
#include "prahangine/pr4/types.h"
#include "prahangine/pr4/errors.h"

class AssetSystem {
public:
    Header header;
    std::vector<Mesh> meshes;
    std::vector<Object> objects;
    std::vector<Animation> animations;

    AssetSystem() = default;

    PR4_LOAD_ERROR load(const char* path);
    PR4_WRITER_ERROR write(const char* path);
};
