//
// Created by João Fernandes on 15/05/2024.
//

#include "ObjUtil.h"

#include <sstream>
#include <glm/glm.hpp>
#include "FileUtil.hpp"

bool LoadOBJ(const std::string& path) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices, temp_normals;
    std::vector<glm::vec2> temp_uvs;

    ReadFile(path, [&temp_vertices, &temp_uvs, &temp_normals](const std::string& line) {
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
            // Generate faces
        }
    });

    std::cout << "Vertices: " << temp_vertices.size() << std::endl;
}
