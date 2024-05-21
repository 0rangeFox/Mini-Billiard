//
// Created by João Fernandes on 13/05/2024.
//

#include "Application.h"

#include <cstdlib>
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
    this->aspectRatio = float(this->width) / float(this->height);
    this->textures = new std::unordered_map<GLuint, GLuint>();
    glewExperimental = GL_TRUE;

    std::srand((unsigned int) std::time(nullptr));
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) return;

#if _WIN32 || _WIN64
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
#elif __APPLE__
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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
    this->isInitialized = this->camera.initialize(glm::vec3(0.f, 10.f, 20.f));
}

Application::~Application() {
    glfwDestroyWindow(this->actualWindow);

    for (const ObjectRenderable* obj : this->objects)
        delete obj;

    for (auto tex : *this->textures)
        glDeleteTextures(1, &tex.second);

    glfwTerminate();

    delete this->textures;
}

// Unbind the actual VAO, VBO, EBO, Texture and Shaders
void unbindBuffers() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Application::addObject(ObjectRenderable* obj) {
    bool isAssembledSuccessfully = obj->assemble(this);

    unbindBuffers();

    if (isAssembledSuccessfully)
        this->objects.push_back(obj);
    return isAssembledSuccessfully;
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

    glfwSetWindowUserPointer(this->actualWindow, this);

    // Initialize mouse interceptors
    glfwSetMouseButtonCallback(this->actualWindow, MouseButtonCallback);
    glfwSetCursorPosCallback(this->actualWindow, MouseMoveCallback);
    glfwSetScrollCallback(this->actualWindow, MouseScrollCallback);

    glClearColor(.1f, .1f, .1f, 1.f);

    while (!glfwWindowShouldClose(this->actualWindow)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const ObjectRenderable* obj : this->objects)
            obj->render(this);
        unbindBuffers();

        glfwSwapBuffers(this->actualWindow);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}
