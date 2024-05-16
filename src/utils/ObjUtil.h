//
// Created by João Fernandes on 15/05/2024.
//

#ifndef MINI_BILLIARD_OBJUTIL_H
#define MINI_BILLIARD_OBJUTIL_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#define HEADER_VERTEX "v "
#define HEADER_TEXTURE "vt"
#define HEADER_NORMAL "vn"
#define HEADER_FACE 'f'

bool LoadOBJ(const std::string&, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&);

#endif //MINI_BILLIARD_OBJUTIL_H
