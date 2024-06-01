#ifndef MINI_BILLIARD_FRAMEBUFFERSIZECALLBACK_HPP
#define MINI_BILLIARD_FRAMEBUFFERSIZECALLBACK_HPP

#include "../app/Application.h"

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    auto app = (Application*) glfwGetWindowUserPointer(window);
    app->updateResolution(width, height);
}

#endif //MINI_BILLIARD_FRAMEBUFFERSIZECALLBACK_HPP
