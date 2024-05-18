//
// Created by João Fernandes on 18/05/2024.
//

#ifndef MINI_BILLIARD_TEXTUREUTIL_HPP
#define MINI_BILLIARD_TEXTUREUTIL_HPP

#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "HashUtil.hpp"

static GLuint LoadTexture(const std::string& name, const std::string& path, bool shouldFlipVertically = false) {
    GLuint textureId = HashString(name.c_str());
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(shouldFlipVertically);

    int width, height, nChannels;
    stbi_uc* imageData = stbi_load(path.c_str(), &width, &height, &nChannels, 0);

    if (imageData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(imageData);
    } else {
        std::cout << "Error: Can't load the texture \"" << path << "\"." << std::endl;
        return 0;
    }

    return glGetError() == GL_NO_ERROR ? textureId : 0;
}

#endif //MINI_BILLIARD_TEXTUREUTIL_HPP
