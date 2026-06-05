#include <sstream>
#include <fstream>
#include <iostream>

#include "prahangine/render/shaders.h"
#include "pr4/config.h"


std::string loadShaderAsString(const char* path) {
    std::string shaderPath = DATA_PATH + std::string(path);

    std::ifstream file(shaderPath);

    if (!file.is_open()) {
        std::cerr << "Could not open " << shaderPath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
