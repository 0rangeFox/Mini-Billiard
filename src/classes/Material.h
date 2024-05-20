//
// Created by João Fernandes on 16/05/2024.
//

#ifndef MINI_BILLIARD_MATERIAL_H
#define MINI_BILLIARD_MATERIAL_H

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../classes/File.h"

typedef struct {
    File file;

    std::string name; // (newmtl)
    GLfloat specular_exponent; // (Ns)
    glm::vec3 ambient_color; // Coeficiente de reflexão da luz ambiente (Ka)
    glm::vec3 diffuse_color; // (Kd)
    glm::vec3 specular_color; // (Ks)
    File image; // (map_Kd)
} Material, * MaterialPtr;

#endif //MINI_BILLIARD_MATERIAL_H
