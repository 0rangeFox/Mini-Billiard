//
// Created by João Fernandes on 14/05/2024.
//

#ifndef MINI_BILLIARD_ERRORCALLBACK_HPP
#define MINI_BILLIARD_ERRORCALLBACK_HPP

#include <iostream>
#include <GLFW/glfw3.h>

static void ErrorCallback(int error, const char* description) {
    std::cout << "OpenGL Error: " << description << " (Code: " << error << ")" << std::endl;
}

static bool CheckErrorAndLog(const std::string& message) {
    const GLenum error = glGetError();

    if (error == GL_NO_ERROR)
        return true;

    ErrorCallback(error, message.c_str());
    return false;
}

#endif //MINI_BILLIARD_ERRORCALLBACK_HPP
