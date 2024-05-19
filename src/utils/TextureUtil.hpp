//
// Created by João Fernandes on 18/05/2024.
//

#ifndef MINI_BILLIARD_TEXTUREUTIL_HPP
#define MINI_BILLIARD_TEXTUREUTIL_HPP

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../app/Application.h"
#include "../callbacks/ErrorCallback.hpp"
#include "HashUtil.hpp"

static GLuint LoadTexture(const std::string& name, const std::string& path, bool shouldFlipVertically = false, TexturesCache cache = nullptr) {
    GLuint hashedTextureId = HashString(name.c_str());
    GLuint textureId = hashedTextureId;

    if (cache && cache->find(textureId) != cache->end() && glIsTexture(textureId = (*cache)[textureId])) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        return textureId;
    }

    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(shouldFlipVertically);
    stbi_uc* imageData = stbi_load(path.c_str(), &width, &height, &nChannels, 0);

    if (imageData) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glActiveTexture(GL_TEXTURE0);

#if GL_ARB_texture_storage
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, nChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imageData);
#else
        glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height, 0, nChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imageData);
#endif

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        stbi_image_free(imageData);
    } else {
        std::cout << "Error: Can't read the data of image \"" << path << "\"." << std::endl;
        return false;
    }

    if (CheckErrorAndLog("Failed to load the texture \"" + name + "\".")) {
        if (cache)
            cache->insert(std::make_pair(hashedTextureId, textureId));
        return textureId;
    } else return false;
}

static GLuint LoadTexture(const std::string& name, const std::string& path, TexturesCache cache) {
    return LoadTexture(name, path, false, cache);
}

#endif //MINI_BILLIARD_TEXTUREUTIL_HPP
