//
// Created by João Fernandes on 13/05/2024.
//

#include "application.h"

Application::Application(const std::string& title, int width, int height) {
    if (!glfwInit()) return;

    this->actualWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!this->actualWindow)
        return;

    glfwMakeContextCurrent(this->actualWindow);
}

Application::~Application() {
    glfwTerminate();
}

int Application::run() {
    while (!glfwWindowShouldClose(this->actualWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(this->actualWindow);
        glfwPollEvents();
    }

    return 0;
}
