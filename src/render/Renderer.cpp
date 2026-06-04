#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "prahangine/render/Renderer.h"
#include "prahangine/render/shaders.h"


bool Renderer::init(GLFWwindow *window) {
    return loadShader();
}

void Renderer::render(SceneObject& sceneObject, GLuint& VAO, Camera &camera) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    GLint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_TRUE, &sceneObject.modelMatrix.data[0][0]);

    GLint viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_TRUE, &camera.view.data[0][0]);

    GLint projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_TRUE, &camera.projection.data[0][0]);

    glDrawElements(GL_TRIANGLES, sceneObject.mesh.indices.size() * 3, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}

GLuint Renderer::uploadMesh(const Mesh& mesh) {
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        mesh.vertexes.size() * sizeof(Vertex),
        mesh.vertexes.data(),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        mesh.indices.size() * sizeof(Index),
        mesh.indices.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    return VAO;
}

bool Renderer::loadShader() {
    GLuint vertexShader;
    GLuint fragmentShader;

    std::string vertexShaderSource = loadShaderAsString("shaders/vertex.glsl");

    if (vertexShaderSource == "")
        return false;

    const char* vertexShaderText = vertexShaderSource.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
    glCompileShader(vertexShader);

    std::string fragmentShaderSource = loadShaderAsString("shaders/fragment.glsl");

    if (fragmentShaderSource == "")
        return false;

    const char* fragmentShaderText = fragmentShaderSource.c_str();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        printf("Shader program link error: %s\n", log);
        return false;
    }

    return true;
}
