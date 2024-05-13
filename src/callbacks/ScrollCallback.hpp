//
// Created by João Fernandes on 13/05/2024.
//

#ifndef MINI_BILLIARD_SCROLLCALLBACK_HPP
#define MINI_BILLIARD_SCROLLCALLBACK_HPP

#include <GLFW/glfw3.h>
#include "../app/application.h"

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    auto app = (Application*) glfwGetWindowUserPointer(window);

    if (yOffset == 1) // Zoom in
        app->changeZoom(app->getZoom() + fabs(app->getZoom()) * .25f);
    else if (yOffset == -1) // Zoom out
        app->changeZoom(app->getZoom() - fabs(app->getZoom()) * .25f);
}

#endif //MINI_BILLIARD_SCROLLCALLBACK_HPP
