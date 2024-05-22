#ifndef MINI_BILLIARD_MOUSEMOVECALLBACK_HPP
#define MINI_BILLIARD_MOUSEMOVECALLBACK_HPP

#include "../app/Application.h"

static void MouseMoveCallback(GLFWwindow* window, double posX, double posY) {
    auto app = (Application*) glfwGetWindowUserPointer(window);
    MouseCoords mouseCoords = app->updateMouseCoords(posX, posY);

    if (app->isMouseLeftButtonDown()) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        MouseCoord mouseX = std::get<0>(mouseCoords);
        double deltaX = std::get<1>(mouseX) - std::get<0>(mouseX);
        app->getCameraPtr()->updateAngle(deltaX * MOUSE_SENSITIVITY);
    } else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

#endif //MINI_BILLIARD_MOUSEMOVECALLBACK_HPP
