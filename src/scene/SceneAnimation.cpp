#include "prahangine/scene/types.h"

void SceneAnimation::restartAnimation() {
    animTimer = 0.0f;
    currentKeyframeIndex = 0;
    enabled = true;
}

Transform SceneAnimation::updateAnimation(float deltaTime)  {
    if (currentKeyframeIndex == maxKeyframeIndex)
        return animation.keyframes[currentKeyframeIndex].transform;

    animTimer += deltaTime * speed;
    if (animTimer >= frameGap) {
        animTimer = 0.0f;
        currentKeyframeIndex = std::min(currentKeyframeIndex + 1, maxKeyframeIndex);
        if (currentKeyframeIndex == maxKeyframeIndex)
            enabled = false;
    }

    return animation.keyframes[currentKeyframeIndex].transform;
}
