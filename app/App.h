#pragma once
#include "GLFW/glfw3.h"
#include "prahangine/pr4/AssetSystem.h"
#include "prahangine/render/Renderer.h"


class App {
public:
    App();
    bool init();
    void run();

private:
    GLFWwindow* window;
    Renderer renderer;
    AssetSystem assetSystem;
    SceneObject sceneObject;
    GLuint VAO;
};
