#pragma once
#include "GLFW/glfw3.h"
#include "prahangine/camera/Camera.h"
#include "pr4/AssetSystem.h"
#include "prahangine/render/Renderer.h"


class App {
public:
    App();
    bool init();
    void run();
    void update(float deltaTime);
    void restart();

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

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
