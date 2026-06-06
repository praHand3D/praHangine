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

        for (int i = 0; i < sceneObjects.size(); i++) {
            renderer.render(sceneObjects[i], VAOs[i], camera);
        }

        glfwSwapBuffers(window);
    }
}

void App::update(float deltaTime) {
    for (SceneObject& sceneObject : sceneObjects) {
        if (sceneObject.animation && sceneObject.animation->enabled) {
            Transform t = sceneObject.animation->updateAnimation(deltaTime);
            sceneObject.object.transform = t;
            sceneObject.updateModelMatrix();
        }
    }
}

void App::restart() {
    for (SceneObject& sceneObject : sceneObjects)
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

    this->window = glfwCreateWindow(1400, 800, "praHangine", NULL, NULL);

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
    std::string dataPathString = DATA_PATH + "obr.PR4";
    assetSystem.load(dataPathString.c_str());

    for (Object& obj : assetSystem.objects) {
        Mesh& mesh = assetSystem.meshes.at(obj.mesh_ref);
        SceneObject scene_object = SceneObject(obj, mesh);

        for (Animation& anim : assetSystem.animations)
            if (anim.object_ref == obj.id)
                scene_object.animation = anim;

        sceneObjects.push_back(scene_object);

        GLuint vao = renderer.uploadMesh(scene_object.mesh);
        VAOs.push_back(vao);
    }

    return true;
}

void App::initCamera() {
    Vec3 position = Vec3(0, 0, 3);
    Vec3 up = Vec3(0, 1, 0);
    Vec3 target = Vec3(0, 0, 0);

    camera = Camera(position, up, target);
    camera.buildViewMatrix();

    float fov = 100.0f * M_PI / 180.0f;
    float aspectRatio = 1.f;
    float near = 0.1f;
    float far = 100.f;

    camera.buildProjectionMatrix(fov, aspectRatio, near, far);
}
