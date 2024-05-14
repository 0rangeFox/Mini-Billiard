//
// Created by João Fernandes on 13/05/2024.
//

#ifndef MINI_BILLIARD_MOUSESCROLLCALLBACK_HPP
#define MINI_BILLIARD_MOUSESCROLLCALLBACK_HPP

#include <GLFW/glfw3.h>
#include "../app/application.h"

void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    auto app = (Application*) glfwGetWindowUserPointer(window);

    if (yOffset == 1) // Zoom in
        app->updateZoom(fabs(app->getZoom()) * .25f);
    else if (yOffset == -1) // Zoom out
        app->updateZoom(-fabs(app->getZoom()) * .25f);
}

#endif //MINI_BILLIARD_MOUSESCROLLCALLBACK_HPP
