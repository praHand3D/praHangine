#pragma once
#include "GLFW/glfw3.h"
#include "prahangine/camera/Camera.h"
#include "prahangine/pr4/AssetSystem.h"
#include "prahangine/render/Renderer.h"


class App {
public:
    App();
    bool init();
    void run();
    void update(float deltaTime);

private:
    GLFWwindow* window;
    Renderer renderer;
    AssetSystem assetSystem;
    SceneObject sceneObject;
    GLuint VAO;
    Camera camera;

    bool initWindow();
    bool initScene();
    void initCamera();
};
