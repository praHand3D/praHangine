#pragma once

#include "prahangine/math/Matrix.h"
#include "prahangine/pr4/types.h"


struct SceneObject {
    Object object;
    Mesh mesh;
    std::optional<Animation> animation;
    Matrix4x4 modelMatrix;
    // scene position, pivot point?

    SceneObject() {}

    SceneObject(Object object, Mesh mesh) : object(object), mesh(mesh) {
        modelMatrix = buildModelMatrix(object.transform);
    };

    void updateModelMatrix() {
        modelMatrix = buildModelMatrix(object.transform);
    }
};
