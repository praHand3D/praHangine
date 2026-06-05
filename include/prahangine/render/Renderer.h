#pragma once
#include "GLFW/glfw3.h"

#include "pr4/types.h"
#include "prahangine/scene/types.h"
#include "prahangine/camera/Camera.h"


class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    bool init(GLFWwindow* window);
    void render(SceneObject& object, GLuint& VAO, Camera& camera);
    GLuint uploadMesh(const Mesh& mesh);

private:
    GLuint shaderProgram;

    bool loadShader();
};
