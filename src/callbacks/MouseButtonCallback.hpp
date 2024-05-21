//
// Created by João Fernandes on 14/05/2024.
//

#ifndef MINI_BILLIARD_MOUSEBUTTONCALLBACK_HPP
#define MINI_BILLIARD_MOUSEBUTTONCALLBACK_HPP

#include "../app/Application.h"

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto app = (Application*) glfwGetWindowUserPointer(window);

    if (button == GLFW_MOUSE_BUTTON_LEFT)
        app->setMouseLeftButtonDown(action == GLFW_PRESS);
}

#endif //MINI_BILLIARD_MOUSEBUTTONCALLBACK_HPP
