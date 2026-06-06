#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "App.h"
#include "pr4/config.h"
#include "prahangine/camera/Camera.h"


App::App() {}

bool App::init() {
    initCamera();

    if (!initWindow())
        return false;

    if (!initScene())
        return false;

    return true;
}

void App::run() {
    float lastTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        float deltaTime = glfwGetTime() - lastTime;
        update(deltaTime);
        lastTime = glfwGetTime();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.render(sceneObject, VAO, camera);

        glfwSwapBuffers(window);
    }
}

void App::update(float deltaTime) {
    if (sceneObject.animation && sceneObject.animation->enabled) {
        Transform t = sceneObject.animation->updateAnimation(deltaTime);
        sceneObject.object.transform = t;
        sceneObject.updateModelMatrix();
    }
}

void App::restart() {
    if (sceneObject.animation)
        sceneObject.animation->restartAnimation();
}

void App::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        app->restart();
}

bool App::initWindow() {
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

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, App::keyCallback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    return true;
}

bool App::initScene() {
    this->renderer = Renderer();

    if (!renderer.init(this->window))
        return false;

    this->assetSystem = AssetSystem();
    std::string dataPathString = DATA_PATH + "rotated_spot2.PR4";
    assetSystem.load(dataPathString.c_str());

    this->sceneObject = SceneObject(assetSystem.objects[0], assetSystem.meshes[0]);

    if (assetSystem.animations.size() > 0)
        this->sceneObject.animation = SceneAnimation(assetSystem.animations[0]);

    this->VAO = renderer.uploadMesh(sceneObject.mesh);

    return true;
}

void App::initCamera() {
    Vec3 position = Vec3(0, 0, 3);
    Vec3 up = Vec3(0, 1, 0);
    Vec3 target = Vec3(0, 0, 0);

    camera = Camera(position, up, target);
    camera.buildViewMatrix();

    float fov = 44.0f * M_PI / 180.0f;
    float aspectRatio = 1.f;
    float near = 0.1f;
    float far = 100.f;

    camera.buildProjectionMatrix(fov, aspectRatio, near, far);
}
