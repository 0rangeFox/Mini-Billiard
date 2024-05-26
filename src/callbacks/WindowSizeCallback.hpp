//
// Created by João Fernandes on 26/05/2024.
//

#ifndef MINI_BILLIARD_WINDOWSIZECALLBACK_HPP
#define MINI_BILLIARD_WINDOWSIZECALLBACK_HPP

#include "../app/Application.h"

static void WindowSizeCallback(GLFWwindow* window, int width, int height) {
    auto app = (Application*) glfwGetWindowUserPointer(window);
    app->updateResolution(width, height);
}

#endif //MINI_BILLIARD_WINDOWSIZECALLBACK_HPP
