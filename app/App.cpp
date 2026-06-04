#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "App.h"

#include "prahangine/config.h"


void escapePressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

App::App() {}

bool App::init() {
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(444, 444, "praHangine", NULL, NULL);

    if (!this->window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetKeyCallback(window, escapePressCallback);

    this->renderer = Renderer();

    if (!renderer.init(this->window))
        return false;

    this->assetSystem = AssetSystem();
    std::string dataPathString = DATA_PATH + "cube.PR4";
    assetSystem.load(dataPathString.c_str());

    this->sceneObject = SceneObject(assetSystem.objects[0], assetSystem.meshes[0]);

    this->VAO = renderer.uploadMesh(sceneObject.mesh);

    return true;
}

void App::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.render(sceneObject, VAO);

        glfwSwapBuffers(window);
    }
}
