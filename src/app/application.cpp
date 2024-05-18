//
// Created by João Fernandes on 13/05/2024.
//

#include "application.h"

#include "../callbacks/ErrorCallback.hpp"
#include "../callbacks/MouseButtonCallback.hpp"
#include "../callbacks/MouseMoveCallback.hpp"
#include "../callbacks/MouseScrollCallback.hpp"

Application::Application(const char* title, int width, int height) {
    this->width = width;
    this->height = height;
    this->zoom = 10.f;
    this->angle = 0.f;
    glewExperimental = GL_TRUE;

    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

#if _WIN32 || _WIN64
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
#elif __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->actualWindow = glfwCreateWindow(this->width, this->height, title, nullptr, nullptr);
    glfwMakeContextCurrent(this->actualWindow);

    if (!this->actualWindow || glewInit() != GLEW_OK || !this->setupVAOsAndVBOs())
        return;

    glViewport(0, 0, this->width, this->height);
}

Application::~Application() {
    glfwTerminate();

    for (const ObjectRenderable* obj : this->objects)
        delete obj;
}

void Application::addObject(ObjectRenderable* obj) {
    obj->assemble(this);
    this->objects.push_back(obj);
}

float Application::setAngle(float angle) {
    float oldAngle = this->angle;
    this->angle = angle;
    this->updateCamera();
    return oldAngle;
}

float Application::updateAngle(float angle) {
    float newAngle = this->angle + angle;
    this->setAngle(newAngle);
    return angle;
}

float Application::setZoom(float zoom) {
    float oldZoom = this->zoom;
    this->zoom = zoom;
    this->updateCamera();
    return oldZoom;
}

float Application::updateZoom(float zoom) {
    float newZoom = this->zoom + zoom;
    this->setZoom(newZoom);
    return newZoom;
}

void Application::updateCamera() {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(this->width) / float(this->height), 0.1f, 100.f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 5.0f, this->zoom),
        glm::vec3(0.0f, 0.f, -1.0f),
        glm::vec3(0.0f, 1.f, 0.0f)
    );

    // Rotations
    // https://www.songho.ca/opengl/files/gl_camera07.jpg
    // https://learnopengl.com/img/getting-started/camera_pitch_yaw_roll.png
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), this->angle, glm::normalize(glm::vec3(0.f, 1.f, 0.f)));

    this->mvp = projection * view * model;
}

bool Application::setupVAOsAndVBOs() {
    GLint maxVAOs, maxVBOs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVAOs);
    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &maxVBOs);

    if (VAOs > maxVAOs || VBOs > maxVBOs)
        return false;

    glGenVertexArrays(VAOs, this->VAO);
    glGenBuffers(VBOs, this->VBO);

    return true;
}

int Application::run() {
    this->updateCamera();

    glfwSetWindowUserPointer(this->actualWindow, this);

    // Initialize mouse interceptors
    glfwSetMouseButtonCallback(this->actualWindow, MouseButtonCallback);
    glfwSetCursorPosCallback(this->actualWindow, MouseMoveCallback);
    glfwSetScrollCallback(this->actualWindow, MouseScrollCallback);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(this->actualWindow)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const ObjectRenderable* obj : this->objects)
            obj->render(this);

        glfwSwapBuffers(this->actualWindow);
        glfwPollEvents();
    }

    return 0;
}
