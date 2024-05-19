//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_GLMACRO_HPP
#define MINI_BILLIARD_GLMACRO_HPP

#if _WIN32 || _WIN64
    #define glBufferStore(type, data, size) \
        glBufferStorage(type, size, data, 0);

    #define glGetProgramResLoc(program, name) \
        glGetProgramResourceLocation(program, GL_PROGRAM_INPUT, name);
#elif __APPLE__
    #define glBufferStore(type, data, size) \
        glBufferData(type, size, data, GL_STATIC_DRAW);

    #define glGetProgramResLoc(program, name) \
        glGetAttribLocation(program, name);
#endif

#endif //MINI_BILLIARD_GLMACRO_HPP
