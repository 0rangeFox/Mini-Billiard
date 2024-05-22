#ifndef MINI_BILLIARD_GLMACRO_HPP
#define MINI_BILLIARD_GLMACRO_HPP

#if _WIN32 || _WIN64
    #define glGetProgramResLoc(program, name) \
        glGetProgramResourceLocation(program, GL_PROGRAM_INPUT, name);
#elif __APPLE__
    #define glGetProgramResLoc(program, name) \
        glGetAttribLocation(program, name);
#endif

#endif //MINI_BILLIARD_GLMACRO_HPP
