//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_MATERIALUTIL_HPP
#define MINI_BILLIARD_MATERIALUTIL_HPP

#include "FileUtil.hpp"
#include "../classes/Material.h"

#define HEADER_NAME "newmtl"
#define HEADER_SPECULAR_EXP "Ns"
#define HEADER_AMBIENTE_COLOR "Ka"
#define HEADER_DIFFUSE_COLOR "Kd"
#define HEADER_SPECULAR_COLOR "Ks"
#define HEADER_IMAGE "map_Kd"

static MaterialPtr LoadMaterial(const std::string& path) {
    auto* material = new Material{};
    if (!ReadFile(path, [material](const std::string& line) {
        if (!line.rfind(HEADER_NAME))
            std::istringstream(line.substr(6)) >> material->name;
        else if (!line.rfind(HEADER_SPECULAR_EXP))
            std::istringstream(line.substr(2)) >> material->specular_exponent;
        else if (!line.rfind(HEADER_AMBIENTE_COLOR))
            std::istringstream(line.substr(2)) >> material->ambient_color.r >> material->ambient_color.g >> material->ambient_color.b;
        else if (!line.rfind(HEADER_DIFFUSE_COLOR))
            std::istringstream(line.substr(2)) >> material->diffuse_color.r >> material->diffuse_color.g >> material->diffuse_color.b;
        else if (!line.rfind(HEADER_SPECULAR_COLOR))
            std::istringstream(line.substr(2)) >> material->specular_color.r >> material->specular_color.g >> material->specular_color.b;
        else if (!line.rfind(HEADER_IMAGE))
            std::istringstream(line.substr(6)) >> material->image;

        return true;
    }))
        return nullptr;

    return material;
}

#endif //MINI_BILLIARD_MATERIALUTIL_HPP
