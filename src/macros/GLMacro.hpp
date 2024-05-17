//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_GLMACRO_HPP
#define MINI_BILLIARD_GLMACRO_HPP

#if _WIN32 || _WIN64
    #define glBufferStore(data, size) \
        glBufferStorage(GL_ARRAY_BUFFER, size, data, 0);
#elif __APPLE__
    #define glBufferStore(data, size) \
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
#endif

#endif //MINI_BILLIARD_GLMACRO_HPP
