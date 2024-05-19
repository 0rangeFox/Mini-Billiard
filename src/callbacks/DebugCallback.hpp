//
// Created by João Fernandes on 19/05/2024.
//

#ifndef MINI_BILLIARD_DEBUGCALLBACK_HPP
#define MINI_BILLIARD_DEBUGCALLBACK_HPP

#include <stdio.h>
#include <GL/glew.h>

static void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message);
}

#endif //MINI_BILLIARD_DEBUGCALLBACK_HPP
