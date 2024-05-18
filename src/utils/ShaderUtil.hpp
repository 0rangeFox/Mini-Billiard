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

static GLuint UnloadShaderAndLogError(const GLuint& program, Shader* shader, const std::string& message) {
    GLint infoLogLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    std::vector<GLchar> infoLog(infoLogLength);
    glGetProgramInfoLog(program, infoLogLength, &infoLogLength, &infoLog[0]);

    std::cout << message << std::endl << infoLog.data() << std::endl;

    return UnloadShader(shader);
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

        GLint isCompiled;
        glGetShaderiv(shader[i].component, GL_COMPILE_STATUS, &isCompiled);

        if (!isCompiled)
            return UnloadShaderAndLogError(program, shader, "Error: failed to compile " + std::string(shader[i].type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader.");

        glAttachShader(program, shader[i].component);
    }

    glLinkProgram(program);

    GLint isLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    return isLinked ? program : UnloadShaderAndLogError(program, shader, "Error: failed to link the shader.");
}

#endif //MINI_BILLIARD_SHADERUTIL_HPP
