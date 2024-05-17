//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_SHADERUTIL_HPP
#define MINI_BILLIARD_SHADERUTIL_HPP

#include <GLFW/glfw3.h>
#include "FileUtil.hpp"
#include "StringUtil.hpp"
#include "../classes/Shader.h"

static GLuint UnloadShader(Shader* shader) {
    for (GLint i = 0; shader[i].type != GL_NONE; i++) {
        if (shader[i].component != 0)
            glDeleteShader(shader[i].component);
        shader[i].component = 0;
    }

    return 0;
}

static GLuint LoadShader(Shader* shader) {
    if (!shader) return 0;

    GLuint program = glCreateProgram();

    for (GLint i = 0; shader[i].type != GL_NONE; i++) {
        shader[i].component = glCreateShader(shader[i].type);

        const std::string& contents = GetStringFromVector(ReadFile(shader[i].filename));

        if (contents.empty())
            return UnloadShader(shader);

        glShaderSource(shader[i].component, 1, (const char* const *) contents.c_str(), nullptr);
        glCompileShader(shader[i].component);

        GLint compiled;
        glGetShaderiv(shader[i].component, GL_COMPILE_STATUS, &compiled);

        if (!compiled)
            return UnloadShader(shader);

        glAttachShader(program, shader[i].component);
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    return linked ? program : UnloadShader(shader);
}

#endif //MINI_BILLIARD_SHADERUTIL_HPP
