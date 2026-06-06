#pragma once

#include <optional>

#include "math/Matrix.h"
#include "pr4/types.h"


struct SceneAnimation {
    Animation animation;
    float animTimer;
    int currentKeyframeIndex;
    int maxKeyframeIndex;
    float frameGap;
    float speed;
    bool enabled;

    SceneAnimation(Animation animation):
        animation(animation),
        animTimer(0.0f),
        currentKeyframeIndex(0),
        maxKeyframeIndex(animation.keyframes.size()-1),
        frameGap(1.0f/animation.fps),
        speed(0.5f),
        enabled(true){};

    void restartAnimation();

    Transform updateAnimation(float deltaTime);
};

struct SceneObject {
    Object object;
    Mesh mesh;
    std::optional<SceneAnimation> animation;
    Matrix4x4 modelMatrix;
    // scene position, pivot point?

    SceneObject() {}

    SceneObject(Object object, Mesh mesh) : object(object), mesh(mesh) {
        modelMatrix = buildModelMatrix(object.transform);
    };

    void updateTransform(float deltaTime) {
        if (animation)
            object.transform = animation->updateAnimation(deltaTime);

        updateModelMatrix();
    }

    void updateModelMatrix() {
        modelMatrix = buildModelMatrix(object.transform);
    }
};
