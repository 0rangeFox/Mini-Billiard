//
// Created by João Fernandes on 13/05/2024.
//

#include "Application.h"

#include <chrono>
#if _WIN32 || _WIN64
#include "../callbacks/DebugCallback.hpp"
#endif
#include "../callbacks/ErrorCallback.hpp"
#include "../callbacks/MouseButtonCallback.hpp"
#include "../callbacks/MouseMoveCallback.hpp"
#include "../callbacks/MouseScrollCallback.hpp"
#include "../classes/ObjectRenderable.h"

Application::Application(const char* title, int width, int height) {
    this->width = width;
    this->height = height;
    this->zoom = 10.f;
    this->angle = 0.f;
    this->textures = new std::unordered_map<GLuint, GLuint>();
    glewExperimental = GL_TRUE;

    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) return;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
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

#if _WIN32 || _WIN64
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugCallback, nullptr);
#endif

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, this->width, this->height);

    this->isInitialized = true;
}

Application::~Application() {
    glfwTerminate();

    for (const ObjectRenderable* obj : this->objects)
        delete obj;

    for (auto tex : *this->textures) {
        glBindTexture(GL_TEXTURE_2D, tex.second);
        std::cout << tex.second << " | " << (int) glIsTexture(tex.second) << std::endl;
        glDeleteTextures(1, &tex.second);
        std::cout << tex.second << " | " << (int) glIsTexture(tex.second) << std::endl;
    }


    delete this->textures;
}

bool Application::addObject(ObjectRenderable* obj) {
    bool isAssembledSuccessfully = obj->assemble(this);
    if (isAssembledSuccessfully)
        this->objects.push_back(obj);
    return isAssembledSuccessfully;
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

template<typename T, typename R>
GLint getMaxVAOs(const std::chrono::duration<T, R>& duration) {
    std::vector<GLuint> vVAOs;
    auto startTime = std::chrono::high_resolution_clock::now();

    do {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        vVAOs.push_back(vao);
    } while (glGetError() == GL_NO_ERROR && std::chrono::high_resolution_clock::now() - startTime <= duration);

    for (GLuint vao : vVAOs)
        glDeleteVertexArrays(1, &vao);

    return vVAOs.size();
}

bool Application::setupVAOsAndVBOs() {
    GLint maxVAOs = getMaxVAOs(std::chrono::microseconds(60)), maxVBOs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVBOs);

    if (VAOs > maxVAOs || VBOs > maxVBOs)
        return false;

    glGenVertexArrays(VAOs, this->VAO);
    glGenBuffers(VBOs, this->VBO);

    return true;
}

int Application::run() {
    if (!this->isInitialized)
        return EXIT_FAILURE;

    this->updateCamera();

    glfwSetWindowUserPointer(this->actualWindow, this);

    // Initialize mouse interceptors
    glfwSetMouseButtonCallback(this->actualWindow, MouseButtonCallback);
    glfwSetCursorPosCallback(this->actualWindow, MouseMoveCallback);
    glfwSetScrollCallback(this->actualWindow, MouseScrollCallback);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(this->actualWindow)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const ObjectRenderable* obj : this->objects)
            obj->render(this);

        glfwSwapBuffers(this->actualWindow);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}
