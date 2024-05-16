//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTUTIL_HPP
#define MINI_BILLIARD_OBJECTUTIL_HPP

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "FileUtil.hpp"

#define HEADER_MATERIAL "mtllib"
#define HEADER_VERTEX "v "
#define HEADER_TEXTURE "vt"
#define HEADER_NORMAL "vn"
#define HEADER_FACE 'f'

static bool LoadOBJ(const std::string& path, std::string& material, std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices, temp_normals;
    std::vector<glm::vec2> temp_uvs;

    if (!ReadFile(path, [&material, &temp_vertices, &temp_uvs, &temp_normals, &vertexIndices, &uvIndices, &normalIndices](const std::string& line) {
        if (!line.rfind(HEADER_MATERIAL)) {
            std::istringstream(line.substr(6)) >> material;
        } else if (!line.rfind(HEADER_VERTEX)) {
            glm::vec3 vertex;
            std::istringstream(line.substr(1)) >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);
        } else if (!line.rfind(HEADER_TEXTURE)){
            glm::vec2 uv;
            std::istringstream(line.substr(2)) >> uv.x >> uv.y;
            temp_uvs.push_back(uv);
        } else if (!line.rfind(HEADER_NORMAL)) {
            glm::vec3 normal;
            std::istringstream(line.substr(2)) >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        } else if (!line.rfind(HEADER_FACE)) {
#define VERTICES 3
            unsigned int vertexIndex[VERTICES], uvIndex[VERTICES], normalIndex[VERTICES];

            int matches = sscanf(line.substr(1).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                std::cout << "Couldn't parse the line \"" << line << "\"." << std::endl;
                return false;
            }

            for (int i = 0; i < VERTICES; ++i) {
                vertexIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalIndices.push_back(normalIndex[i]);
            }
        }

        return true;
    }))
        return false;

    for (unsigned int vertexIndex : vertexIndices)
        vertices.push_back(temp_vertices[vertexIndex - 1]);

    for (unsigned int uvIndex : uvIndices)
        uvs.push_back(temp_uvs[uvIndex - 1]);

    for (unsigned int normalIndex : normalIndices)
        normals.push_back(temp_normals[normalIndex - 1]);

    return true;
}

#endif //MINI_BILLIARD_OBJECTUTIL_HPP
