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
    auto* material = new Material{ File(path) };
    if (!ReadFileStream(path, [material](std::istringstream line) {
        std::string header;
        line >> header;

        if (header == HEADER_NAME)
            line >> material->name;
        else if (header == HEADER_SPECULAR_EXP)
            line >> material->specular_exponent;
        else if (header == HEADER_AMBIENTE_COLOR)
            line >> material->ambient_color.r >> material->ambient_color.g >> material->ambient_color.b;
        else if (header == HEADER_DIFFUSE_COLOR)
            line >> material->diffuse_color.r >> material->diffuse_color.g >> material->diffuse_color.b;
        else if (header == HEADER_SPECULAR_COLOR)
            line >> material->specular_color.r >> material->specular_color.g >> material->specular_color.b;
        else if (header == HEADER_IMAGE) {
            line >> header;
            material->image = material->file.copyPathToFile(header);
        }

        return true;
    }))
        return nullptr;
    return material;
}

#endif //MINI_BILLIARD_MATERIALUTIL_HPP
