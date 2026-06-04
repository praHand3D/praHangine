#include <sstream>
#include <fstream>

#include "prahangine/render/shaders.h"

#include <iostream>

#include "prahangine/config.h"


std::string loadShader(const char* path) {
    std::string shaderPath = DATA_PATH + std::string(path);

    std::ifstream file(shaderPath);

    if (!file.is_open()) {
        std::cerr << "Could not open " << shaderPath << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
