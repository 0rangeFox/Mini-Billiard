//
// Created by João Fernandes on 16/05/2024.
//

#ifndef MINI_BILLIARD_MATERIAL_H
#define MINI_BILLIARD_MATERIAL_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Material {
    std::string name; // (newmtl)
    GLfloat specular_exponent; // (Ns)
    glm::vec3 ambient_color; // Coeficiente de reflexão da luz ambiente (Ka)
    glm::vec3 diffuse_color; // (Kd)
    glm::vec3 specular_color; // (Ks)
    std::string image; // (map_Kd)
};

#endif //MINI_BILLIARD_MATERIAL_H
