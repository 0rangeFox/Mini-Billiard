#ifndef MINI_BILLIARD_SHADERUTIL_HPP
#define MINI_BILLIARD_SHADERUTIL_HPP

#include "FileUtil.hpp"
#include "StringUtil.hpp"
#include "../classes/Shader.h"

static GLuint UnloadShader(ShaderPtr shader) {
    for (GLint i = 0; shader[i].type != GL_NONE; i++) {
        if (shader[i].component != 0)
            glDeleteShader(shader[i].component);
        shader[i].component = 0;
    }

    return 0;
}

static GLuint UnloadShaderAndLogError(const GLuint& program, ShaderPtr shader, const std::string& message) {
    if (!program) {
        std::cout << message << std::endl;
        return 0;
    }

    GLint infoLogLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    std::vector<GLchar> infoLog(infoLogLength);
    glGetProgramInfoLog(program, infoLogLength, &infoLogLength, infoLog.data());

    std::cout << message << std::endl << infoLog.data() << std::endl;

    glDeleteProgram(program);
    return UnloadShader(shader);
}

static GLuint LoadShader(ShaderPtr shader) {
    if (!shader) return 0;

    GLuint program = glCreateProgram();

    if (!program)
        return UnloadShaderAndLogError(program, shader, "Error: unable to create shader program.");

    for (GLint i = 0; shader[i].type != GL_NONE; i++) {
        shader[i].component = glCreateShader(shader[i].type);

        const std::string& fileContents = GetStringFromVector(ReadFile(shader[i].file->getFullPath()));
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

    if (!isLinked)
        return UnloadShaderAndLogError(program, shader, "Error: failed to link the shader.");

    glValidateProgram(program);

    GLint isValidated;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &isValidated);

    return isValidated ? program : UnloadShaderAndLogError(program, shader, "Error: failed to validate the shader.");
}

#endif //MINI_BILLIARD_SHADERUTIL_HPP
