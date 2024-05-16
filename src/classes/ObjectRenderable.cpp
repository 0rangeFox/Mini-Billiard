//
// Created by João Fernandes on 16/05/2024.
//

#include "ObjectRenderable.h"

#include "../app/application.h"
#include <GL/glew.h>

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path) {
    std::string _material {};

    this->type = type;
    this->isInitialized = LoadOBJ(path, _material, this->vertices, this->uvs, this->normals);

    if (!_material.empty())
        this->material = LoadMaterial();
}

ObjectRenderable::~ObjectRenderable() {
    delete this->material;
}

GLuint ObjectRenderable::generateVertex(GLfloat* floats) const {
    GLuint counter = 0;

    for (int i = 0; i < this->vertices.size(); i++) {
        glm::vec3 vertices = this->vertices[i];
        glm::vec3 normals = this->normals[i];
        glm::vec2 uvs = this->uvs[i];

        // X Y Z
        floats[counter++] = vertices.x;
        floats[counter++] = vertices.y;
        floats[counter++] = vertices.z;

        // NX NY NZ
        floats[counter++] = normals.x;
        floats[counter++] = normals.y;
        floats[counter++] = normals.z;

        // X Y
        floats[counter++] = uvs.x;
        floats[counter++] = uvs.y;
    }

    return counter;
}

void ObjectRenderable::render(const Application* app) const {
    if (!this->isInitialized) return;

    glBindVertexArray(app->VAO[this->type]);
    glBindBuffer(GL_ARRAY_BUFFER, app->VBO[0]);

    GLfloat base[this->getTotalVertices()];
    this->generateVertex(base);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(base), base, GL_STATIC_DRAW);

    auto coordsId = 0;
    GLsizei stride = sizeof(float) * (3 + 3 + 2);
    glVertexAttribPointer(coordsId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) 0);
    glVertexAttribPointer(coordsId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) 3);
    glVertexAttribPointer(coordsId, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *) 6);



}
