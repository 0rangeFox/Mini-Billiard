//
// Created by João Fernandes on 16/05/2024.
//

#include "ObjectRenderable.h"

#include "../app/application.h"
#include <GL/glew.h>

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path) {
    this->type = type;
    this->isInitialized = LoadOBJ(path, this->vertices, this->uvs, this->normals);
}

void ObjectRenderable::render(const Application* app) const {
    if (!this->isInitialized) return;

    glBindVertexArray(app->VAO[this->type]);
    glBindBuffer(GL_ARRAY_BUFFER, app->VBO[0]);

    glBufferStorage(GL_ARRAY_BUFFER, this->vertices.size(), &this->vertices[0], 0);
}
