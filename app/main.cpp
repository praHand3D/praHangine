#include <GLFW/glfw3.h>


GLFWwindow* createWindow() {
    if (!glfwInit())
        return nullptr;

    GLFWwindow *window = glfwCreateWindow(444, 444, "praHangine", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    return window;
}

void loop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

int main() {
    GLFWwindow* window = createWindow();
    if (!window) return -1;

    loop(window);

    glfwTerminate();
    return 0;
}
