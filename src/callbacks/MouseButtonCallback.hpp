//
// Created by João Fernandes on 14/05/2024.
//

#ifndef MINI_BILLIARD_MOUSEBUTTONCALLBACK_HPP
#define MINI_BILLIARD_MOUSEBUTTONCALLBACK_HPP

#include "../app/Application.h"

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto app = (Application*) glfwGetWindowUserPointer(window);

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS)
            app->setMouseLeftButtonDown(true);
        else if (action == GLFW_RELEASE) {
            app->setMouseLeftButtonDown(false);
            app->getCameraPtr()->setAngle(0);
        }

    }
}

#endif //MINI_BILLIARD_MOUSEBUTTONCALLBACK_HPP
