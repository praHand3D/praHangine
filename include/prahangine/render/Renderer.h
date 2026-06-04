#pragma once
#include "GLFW/glfw3.h"

#include "prahangine/scene/types.h"


class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    bool init(GLFWwindow* window);
    void render(SceneObject& object, GLuint& VAO);
    GLuint uploadMesh(const Mesh& mesh);

private:
    GLuint shaderProgram;

    bool loadShader();
};
