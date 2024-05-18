//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_SHADER_H
#define MINI_BILLIARD_SHADER_H

#include <GL/glew.h>

typedef struct {
    GLenum type;
    const char* filename;
    GLuint component;
} Shader;

#endif //MINI_BILLIARD_SHADER_H
