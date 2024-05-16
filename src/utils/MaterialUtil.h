#ifndef MINI_BILLIARD_MATERIALUTIL_H
#define MINI_BILLIARD_MATERIALUTIL_H
#define HEADER_NAME "newmtl "
#define HEADER_SPECULAR_EXP "Ns "
#define HEADER_AMBIENTE_COLOR "Ka "
#define HEADER_DIFFUSE_COLOR "Kd "
#define HEADER_SPECULAR_COLOR "Ks "
#define HEADER_IMAGE "map_Kd "

#include <iostream>
#include "../classes/Material.h"

Material* LoadMaterial(const std::string& path);

#endif //MINI_BILLIARD_MATERIALUTIL_H
