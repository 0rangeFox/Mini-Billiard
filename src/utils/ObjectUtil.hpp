//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTUTIL_HPP
#define MINI_BILLIARD_OBJECTUTIL_HPP

#include <glm/glm.hpp>
#include "FileUtil.hpp"

#define HEADER_MATERIAL "mtllib"
#define HEADER_VERTEX "v"
#define HEADER_TEXTURE "vt"
#define HEADER_NORMAL "vn"
#define HEADER_FACE "f"

static void GenerateElements(std::vector<GLfloat>& elements, const glm::vec3& vVertices, const glm::vec2& vUVs, const glm::vec3& vNormals) {
    // X Y Z
    elements.push_back(vVertices.x);
    elements.push_back(vVertices.y);
    elements.push_back(vVertices.z);

    // U V
    elements.push_back(vUVs.x);
    elements.push_back(vUVs.y);

    // NX NY NZ
    elements.push_back(vNormals.x);
    elements.push_back(vNormals.y);
    elements.push_back(vNormals.z);

}

static bool LoadOBJ(const std::string& path, std::string& material, std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals, std::vector<GLuint>& indices, std::vector<GLfloat>& elements) {
    if (!ReadFileStream(path, [&material, &vertices, &uvs, &normals, &indices, &elements](std::istringstream line) {
        std::string header;
        line >> header;

        if (header == HEADER_MATERIAL) {
            line >> material;
        } else if (header == HEADER_VERTEX) {
            glm::vec3 vertex;
            line >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (header == HEADER_TEXTURE){
            glm::vec2 uv;
            line >> uv.x >> uv.y;
            uvs.push_back(uv);
        } else if (header == HEADER_NORMAL) {
            glm::vec3 normal;
            line >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (header == HEADER_FACE) {
            #define VERTICES 3
            char skipChar;
            unsigned int vertexIndex, uvIndex, normalIndex;

            for (int i = 0; i < VERTICES; ++i) {
                line >> vertexIndex >> skipChar >> uvIndex >> skipChar >> normalIndex;
                indices.push_back(indices.size());
                GenerateElements(elements, vertices[vertexIndex - 1], uvs[uvIndex - 1], normals[normalIndex - 1]);
            }
        }

        return true;
    }))
        return false;
    return true;
}

#endif //MINI_BILLIARD_OBJECTUTIL_HPP
