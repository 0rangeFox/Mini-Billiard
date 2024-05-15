//
// Created by João Fernandes on 15/05/2024.
//

#include "ObjUtil.h"

#include <sstream>
#include "FileUtil.hpp"

bool LoadOBJ(const std::string& path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices, temp_normals;
    std::vector<glm::vec2> temp_uvs;

    ReadFile(path, [&temp_vertices, &temp_uvs, &temp_normals, &vertexIndices, &uvIndices, &normalIndices](const std::string& line) {
        if (!line.rfind(HEADER_VERTEX)) {
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
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = sscanf(line.substr(1).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                std::cout << "Couldn't parse the line \"" << line << "\"." << std::endl;
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);          
        }
    });

    return true;

}
