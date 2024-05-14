//
// Created by João Fernandes on 14/05/2024.
//

#ifndef MINI_BILLIARD_MOUSECALLBACK_HPP
#define MINI_BILLIARD_MOUSECALLBACK_HPP

#include <tuple>
#include <GLFW/glfw3.h>
#include "../app/application.h"

void MouseCallback(GLFWwindow* window, double posX, double posY) {
    auto app = (Application*) glfwGetWindowUserPointer(window);
    auto mouseCoords = app->updateMouseCoords(posX, posY);

    if (app->isMouseLeftButtonDown()) {
        auto mouseX = get<0>(mouseCoords);
        auto mouseY = get<1>(mouseCoords);

        int dx = get<1>(mouseX) - get<0>(mouseX);
        int dy = get<1>(mouseY) - get<0>(mouseY);

        if (dx < 0) { // Rotating to left side
            if (dy < 0) { // Rotating in Diagonal on Top + Left sides
                app->updateAngle(0.01f);
                return;
            }
        } else if (dx > 0) { // Rotating to right side
            if (dy > 0) { // Rotating in Diagonal on Bottom + Right sides
                app->updateAngle(-0.01f);
                return;
            }
        }
    }
}

#endif //MINI_BILLIARD_MOUSECALLBACK_HPP
