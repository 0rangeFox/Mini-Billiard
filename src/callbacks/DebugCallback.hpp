//
// Created by João Fernandes on 19/05/2024.
//

#ifndef MINI_BILLIARD_DEBUGCALLBACK_HPP
#define MINI_BILLIARD_DEBUGCALLBACK_HPP

#include <stdio.h>
#include <GL/glew.h>

// https://www.khronos.org/opengl/wiki/OpenGL_Error#Catching_errors_.28the_easy_way.29
static void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if (type == GL_DEBUG_TYPE_ERROR)
        fprintf(stderr, "OpenGL ERROR: %s (Code: 0x%x | Severity: 0x%x)\n", message, source, severity);
    else
        fprintf(stdout, "OpenGL INFO: %s\n", message);
}

#endif //MINI_BILLIARD_DEBUGCALLBACK_HPP
