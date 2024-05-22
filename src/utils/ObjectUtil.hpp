#ifndef MINI_BILLIARD_OBJECTUTIL_HPP
#define MINI_BILLIARD_OBJECTUTIL_HPP

#include <glm/glm.hpp>
#include "FileUtil.hpp"

#define HEADER_MATERIAL "mtllib"
#define HEADER_VERTEX "v"
#define HEADER_TEXTURE "vt"
#define HEADER_NORMAL "vn"
#define HEADER_FACE "f"

static void GenerateElements(std::vector<GLfloat>& elements, const glm::vec3* vertices, const glm::vec2* uvs, const glm::vec3* normals) {
    // X Y Z
    if (vertices) {
        elements.push_back(vertices->x);
        elements.push_back(vertices->y);
        elements.push_back(vertices->z);
    } else {
        elements.push_back(0);
        elements.push_back(0);
        elements.push_back(0);
    }

    // U V
    if (uvs) {
        elements.push_back(uvs->x);
        elements.push_back(uvs->y);
    } else {
        elements.push_back(0.f);
        elements.push_back(0.f);
    }

    // NX NY NZ
    if (normals) {
        elements.push_back(normals->x);
        elements.push_back(normals->y);
        elements.push_back(normals->z);
    } else {
        elements.push_back(0);
        elements.push_back(0);
        elements.push_back(0);
    }
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
                GenerateElements(elements, &vertices[--vertexIndex], &uvs[--uvIndex], &normals[--normalIndex]);
            }
        }

        return true;
    }))
        return false;
    return true;
}

#endif //MINI_BILLIARD_OBJECTUTIL_HPP
