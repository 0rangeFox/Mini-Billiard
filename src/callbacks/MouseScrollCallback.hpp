#ifndef MINI_BILLIARD_MOUSESCROLLCALLBACK_HPP
#define MINI_BILLIARD_MOUSESCROLLCALLBACK_HPP

#include "../app/Application.h"

static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    auto app = (Application*) glfwGetWindowUserPointer(window);

    if (yOffset == 1) // Zoom in
        app->getCameraPtr()->updateZoom(.25f);
    else if (yOffset == -1) // Zoom out
        app->getCameraPtr()->updateZoom(-.25f);
}

#endif //MINI_BILLIARD_MOUSESCROLLCALLBACK_HPP
