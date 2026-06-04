#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "prahangine/config.h"
#include "prahangine/render/shaders.h"
#include "prahangine/pr4/AssetSystem.h"
#include "prahangine/scene/types.h"

void escapePressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void loadShaders(GLuint& vertexShader, GLuint& fragmentShader) {
    std::string vertexShaderSource = loadShader("shaders/vertex.glsl");
    const char* vertexShaderText = vertexShaderSource.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
    glCompileShader(vertexShader);

    std::string fragmentShaderSource = loadShader("shaders/fragment.glsl");
    const char* fragmentShaderText = fragmentShaderSource.c_str();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
    glCompileShader(fragmentShader);
}

GLuint setupMesh(const Mesh& mesh) {
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

GLFWwindow* createWindow(GLuint& shaderProgram) {
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(444, 444, "praHangine", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    GLuint vertexShader; GLuint fragmentShader;
    loadShaders(vertexShader, fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glfwSetKeyCallback(window, escapePressCallback);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        printf("Shader program link error: %s\n", log);
    }

    return window;
}

void loop(GLFWwindow* window, GLuint* shaderProgram, GLuint* VAO, SceneObject *scene_object) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(*shaderProgram);
        glBindVertexArray(*VAO);

        GLint loc = glGetUniformLocation(*shaderProgram, "modelMatrix");
        glUniformMatrix4fv(loc, 1, GL_TRUE, &scene_object->modelMatrix.data[0][0]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
}

int main() {
    GLuint shaderProgram;
    GLFWwindow* window = createWindow(shaderProgram);
    if (!window) return -1;

    AssetSystem assetSystem = AssetSystem();
    std::string dataPathString = DATA_PATH + "cube.PR4";
    assetSystem.load(dataPathString.c_str());

    SceneObject scene_object = SceneObject(assetSystem.objects[0], assetSystem.meshes[0]);

    GLuint VAO = setupMesh(scene_object.mesh);

    loop(window, &shaderProgram, &VAO, &scene_object);

    glfwTerminate();
    return 0;
}
