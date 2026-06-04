#include <GLFW/glfw3.h>

#include "App.h"


int main() {
    App app = App();

    if (!app.init())
        return 0;

    app.run();

    glfwTerminate();
    return 0;
}
