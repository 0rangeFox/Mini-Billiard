//
// Created by João Fernandes on 22/05/2024.
//

#ifndef MINI_BILLIARD_KEYBOARDCALLBACK_H
#define MINI_BILLIARD_KEYBOARDCALLBACK_H

#include "../app/Application.h"
#include "../utils/RandomUtil.hpp"

static void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    auto app = (Application *) glfwGetWindowUserPointer(window);

    if (action != GLFW_PRESS)
        return;

    if (key == GLFW_KEY_SPACE)
        app->animateBall(Random(1, TOTAL_BALLS));

    for (int iKey = 0; iKey <= glm::abs(GLFW_KEY_1 - GLFW_KEY_4); iKey++)
        if (key == GLFW_KEY_1 + iKey)
            app->getCameraPtr()->updateLight((LightType) iKey);
}

#endif //MINI_BILLIARD_KEYBOARDCALLBACK_H
