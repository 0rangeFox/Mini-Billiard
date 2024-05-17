//
// Created by João Fernandes on 16/05/2024.
//

#include "ObjectRenderable.h"

#include "../app/application.h"
#include "../utils/ObjectUtil.hpp"
#include "../utils/MaterialUtil.hpp"

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path) {
    std::string _material{};

    this->type = type;
    this->isInitialized = LoadOBJ(path, _material, this->vertices, this->uvs, this->normals);

    if (!_material.empty())
        this->material = LoadMaterial(path.substr(0, path.find_last_of('/')) + "/" + _material);
}

ObjectRenderable::~ObjectRenderable() {
    delete this->material;
}

GLfloat* ObjectRenderable::generateElements() const {
    GLfloat* elements = new GLfloat[this->getTotalElements()];
    GLuint counter = 0;

    for (int i = 0; i < this->vertices.size(); i++) {
        glm::vec3 vVertices = this->vertices[i];
        glm::vec3 vNormals = this->normals[i];
        glm::vec2 vUVs = this->uvs[i];

        // X Y Z
        elements[counter++] = vVertices.x;
        elements[counter++] = vVertices.y;
        elements[counter++] = vVertices.z;

        // NX NY NZ
        elements[counter++] = vNormals.x;
        elements[counter++] = vNormals.y;
        elements[counter++] = vNormals.z;

        // UVX UVY
        elements[counter++] = vUVs.x;
        elements[counter++] = vUVs.y;
    }

    return elements;
}

void ObjectRenderable::render(const Application* app) const {
    if (!this->isInitialized) return;

    glBindVertexArray(app->VAO[this->type]);
    glBindBuffer(GL_ARRAY_BUFFER, app->VBO[0]);

    GLfloat* elements = this->generateElements();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    auto coordsId = 0;
    GLsizei stride = sizeof(float) * (3 + 3 + 2);
    glVertexAttribPointer(coordsId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) 0);
    glVertexAttribPointer(coordsId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) 3);
    glVertexAttribPointer(coordsId, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *) 6);

    delete[] elements;
}
