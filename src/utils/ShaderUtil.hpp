//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_SHADERUTIL_HPP
#define MINI_BILLIARD_SHADERUTIL_HPP

#include <GL/glew.h>
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

        const std::string& fileContents = GetStringFromVector(ReadFile(shader[i].filename));
        if (fileContents.empty())
            return UnloadShader(shader);

        const char* contents = fileContents.c_str();
        glShaderSource(shader[i].component, 1, &contents, nullptr);
        glCompileShader(shader[i].component);

        GLint compiled;
        glGetShaderiv(shader[i].component, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            int length;
            glGetShaderiv(shader[i].component, GL_INFO_LOG_LENGTH, &length);

            char message[50000];
            glGetShaderInfoLog(shader[i].component, length, &length, message);

            std::cout << "Error: failed to compile " << (shader[i].type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << std::endl << message << std::endl;

            return UnloadShader(shader);
        }

        glAttachShader(program, shader[i].component);
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    return linked ? program : UnloadShader(shader);
}

#endif //MINI_BILLIARD_SHADERUTIL_HPP
