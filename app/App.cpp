#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "App.h"
#include "pr4/config.h"
#include "prahangine/camera/Camera.h"
#include "prahangine/input/callback.h"


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
    float speed = 1.0f;
    float angle = deltaTime * speed;

    float s = std::sin(angle / 2.0f);
    float c = std::cos(angle / 2.0f);

    Vec4 delta = {0, s, 0, c};

    sceneObject.object.transform.rotation = Vec4::multiplyQuaternions(sceneObject.object.transform.rotation, delta);

    sceneObject.updateModelMatrix();
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

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetKeyCallback(window, escapePressCallback);

    return true;
}

bool App::initScene() {
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
