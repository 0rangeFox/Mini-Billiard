//
// Created by João Fernandes on 14/05/2024.
//

#ifndef MINI_BILLIARD_MOUSEMOVECALLBACK_HPP
#define MINI_BILLIARD_MOUSEMOVECALLBACK_HPP

#include <tuple>
#include <GLFW/glfw3.h>
#include "../app/application.h"

void MouseMoveCallback(GLFWwindow* window, double posX, double posY) {
    auto app = (Application*) glfwGetWindowUserPointer(window);
    auto mouseCoords = app->updateMouseCoords(posX, posY);

    if (app->isMouseLeftButtonDown()) {
        auto mouseX = std::get<0>(mouseCoords);
        auto mouseY = std::get<1>(mouseCoords);

        int dx = std::get<1>(mouseX) - std::get<0>(mouseX);
        int dy = std::get<1>(mouseY) - std::get<0>(mouseY);

        if (dx < 0) // Rotating to left side
            app->updateAngle(0.01f);
        else if (dx > 0) // Rotating to right side
            app->updateAngle(-0.01f);
    }
}

#endif //MINI_BILLIARD_MOUSEMOVECALLBACK_HPP
