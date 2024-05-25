#ifndef MINI_BILLIARD_SHADER_H
#define MINI_BILLIARD_SHADER_H

#include <GL/glew.h>
#include "../classes/File.h"

typedef struct {
    GLenum type;
    const File* file;

    GLuint program, component;
} Shader, * ShaderPtr;

#endif //MINI_BILLIARD_SHADER_H
