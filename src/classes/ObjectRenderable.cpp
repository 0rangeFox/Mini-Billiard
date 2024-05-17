//
// Created by João Fernandes on 16/05/2024.
//

#include "ObjectRenderable.h"

#include "../macros/GLMacro.hpp"
#include "../app/application.h"
#include "../utils/ObjectUtil.hpp"
#include "../utils/MaterialUtil.hpp"
#include "../utils/ShaderUtil.hpp"

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path) {
    std::string _material{};

    this->type = type;
    this->isInitialized = LoadOBJ(path, _material, this->vertices, this->uvs, this->normals);

    if (!_material.empty())
        this->material = LoadMaterial(path.substr(0, path.find_last_of('/')) + "/" + _material);
}

ObjectRenderable::~ObjectRenderable() {
    glDeleteProgram(this->shader);

    delete this->material;
    delete[] this->elements;
    delete[] this->indices;
}

void ObjectRenderable::generateIndices() {
    this->indices = new GLuint[this->vertices.size()];
    for (int i = 0; i < this->vertices.size(); ++i)
        this->indices[i] = i;
}

void ObjectRenderable::generateElements() {
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

    this->elements = elements;
}

void ObjectRenderable::generateShaders() {
    Shader shaders[] = {
        { GL_VERTEX_SHADER, "shaders/ball.vert" },
        { GL_FRAGMENT_SHADER, "shaders/ball.frag" },
        { GL_NONE, nullptr }
    };

    this->shader = LoadShader(shaders);
}

void ObjectRenderable::assemble(AppPtr app) {
    this->generateElements();
    this->generateIndices();
    this->generateShaders();

    glBindVertexArray(app->VAO[this->type]);

    glBindBuffer(GL_ARRAY_BUFFER, app->VBO[VBO_DATA]);
    glBufferStore(this->elements, this->getTotalElements() * sizeof(GLfloat));

    if (this->indices) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app->VBO[VBO_EBO]);
        glElementBufferStore(this->indices, this->vertices.size() * sizeof(GLuint))
    }

    glUseProgram(this->shader);

    GLint verticesId = glGetProgramResLoc(this->shader, "vVertices")
    GLint normalsId = glGetProgramResLoc(this->shader, "vNormals")
    GLint uvsId = glGetProgramResLoc(this->shader, "vUVs")

    GLsizei stride = sizeof(GLfloat) * (3 + 3 + 2);
    glVertexAttribPointer(verticesId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) 0);
    glVertexAttribPointer(normalsId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) 3);
    glVertexAttribPointer(uvsId, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*) 6);

    glEnableVertexAttribArray(verticesId);
    glEnableVertexAttribArray(normalsId);
    glEnableVertexAttribArray(uvsId);
}

static void updateShaderUniformVariableMVP(GLuint shader, const glm::mat4& mvp) {
    GLint mvpId = glGetUniformLocation(shader, "MVP");
    glProgramUniformMatrix4fv(shader, mvpId, 1, GL_FALSE, glm::value_ptr(mvp));
}

void ObjectRenderable::render(ApplicationPtr app) const {
    if (!this->isInitialized || !this->shader) return;

    glBindVertexArray(app->VAO[this->type]);
    updateShaderUniformVariableMVP(this->shader, app->getMVP());

    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}
