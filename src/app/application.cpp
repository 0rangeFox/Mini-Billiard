//
// Created by João Fernandes on 13/05/2024.
//

#include "application.h"

Application::Application(const std::string& title, int width, int height) {
    this->width = width;
    this->height = height;
    this->zoom = 10.f;
    this->angle = 0.f;

    if (!glfwInit()) return;

    this->actualWindow = glfwCreateWindow(this->width, this->height, title.c_str(), nullptr, nullptr);
    if (!this->actualWindow)
        return;
}

Application::~Application() {
    glfwTerminate();

    for (const ObjectRenderable* obj : this->objects)
        delete obj;
}

void Application::addObject(const ObjectRenderable* obj) {
    this->objects.push_back(obj);
}

void Application::updateCamera(float zoom, float angle) {
    this->zoom = zoom;
    this->angle = angle;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(this->width / this->height), 0.1f, 100.f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, this->zoom),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), this->angle, glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));

    this->mvp = projection * view * model;
}

int Application::run() {
    glfwMakeContextCurrent(this->actualWindow);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(this->actualWindow)) {
        this->updateCamera(this->zoom, this->angle += 0.001f);

        for (const ObjectRenderable* obj : this->objects) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            obj->render(this->mvp);
        }

        glfwSwapBuffers(this->actualWindow);
        glfwPollEvents();
    }

    return 0;
}
