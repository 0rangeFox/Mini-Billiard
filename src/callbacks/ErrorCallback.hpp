#ifndef MINI_BILLIARD_ERRORCALLBACK_HPP
#define MINI_BILLIARD_ERRORCALLBACK_HPP

#include <iostream>
#include <GLFW/glfw3.h>
#include "DebugCallback.hpp"

static void ErrorCallback(int error, const char* message) {
    DebugCallback(error, GL_DEBUG_TYPE_ERROR, 0, 0, 0, message, nullptr);
}

static bool CheckErrorAndLog(const std::string& message) {
    const GLenum error = glGetError();

    if (error == GL_NO_ERROR)
        return true;

    ErrorCallback(error, message.c_str());
    return false;
}

#endif //MINI_BILLIARD_ERRORCALLBACK_HPP
