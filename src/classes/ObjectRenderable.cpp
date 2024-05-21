//
// Created by João Fernandes on 16/05/2024.
//

#include "ObjectRenderable.h"

#include <glm/gtc/type_ptr.hpp>
#include "../macros/GLMacro.hpp"
#include "../utils/ObjectUtil.hpp"
#include "../utils/MaterialUtil.hpp"
#include "../utils/ShaderUtil.hpp"
#include "../utils/TextureUtil.hpp"

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path) : Object(-10, 10) {
    std::string _material{};

    this->position.y = 0;

    this->addResource(FileType::OBJECT, File(path));
    this->type = type;
    this->isInitialized = LoadOBJ(path, _material, this->vertices, this->uvs, this->normals, this->indices, this->elements);

    if (_material.empty())
        return;

    this->addResource(FileType::MATERIAL, this->getResource<FileType::OBJECT>().copyPathToFile(_material));
    this->material = LoadMaterial(this->getResource<FileType::MATERIAL>().getFullPath());

    if (this->material && this->material->image.isValid())
        this->addResource(FileType::IMAGE, this->material->image);
}

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path, const std::unordered_map<FileType, File>& extraFiles) : ObjectRenderable(type, path) {
    this->files.insert(extraFiles.begin(), extraFiles.end());
}

ObjectRenderable::~ObjectRenderable() {
    glDeleteProgram(this->shader);
    delete this->material;
}

bool ObjectRenderable::generateShaders() {
    Shader shaders[] = {
        { GL_VERTEX_SHADER, &this->getResource<FileType::VERTEX_SHADER>() },
        { GL_FRAGMENT_SHADER, &this->getResource<FileType::FRAGMENT_SHADER>() },
        { GL_NONE, nullptr }
    };

    if ((this->shader = LoadShader(shaders)) <= 0)
        return false;

    glUseProgram(this->shader);
    return true;
}

bool ObjectRenderable::generateTextures(ApplicationPtr app) {
    return (this->texture = LoadTexture(this->material->name, this->material->image.getFullPath(), true, app->getTexturesCache())) > 0;
}

bool ObjectRenderable::assemble(ApplicationPtr app) {
    glBindVertexArray(app->getVAO(this->type));

    if (!this->generateShaders() || !this->generateTextures(app))
        return this->isInitialized = false;

    glBindBuffer(GL_ARRAY_BUFFER, app->getVBO(VBO_DATA));
    glBufferStore(GL_ARRAY_BUFFER, this->elements.data(), this->elements.size() * sizeof(GLfloat));

    if (!this->indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app->getVBO(VBO_EBO));
        glBufferStore(GL_ELEMENT_ARRAY_BUFFER, this->indices.data(), this->indices.size() * sizeof(GLuint))
    }

    GLint verticesId = glGetProgramResLoc(this->shader, "vVertices")
    GLint uvsId = glGetProgramResLoc(this->shader, "vUVs")
    GLint normalsId = glGetProgramResLoc(this->shader, "vNormals")

    GLsizei stride = sizeof(GLfloat) * (3 + 2 + 3);
    glVertexAttribPointer(verticesId, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glVertexAttribPointer(uvsId, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*) (3 * sizeof(GLfloat)));
    glVertexAttribPointer(normalsId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) (5 * sizeof(GLfloat)));

    glEnableVertexAttribArray(verticesId);
    glEnableVertexAttribArray(uvsId);
    glEnableVertexAttribArray(normalsId);

    GLint locationTexSampler = glGetUniformLocation(this->shader, "textureMapping");
    glProgramUniform1i(this->shader, locationTexSampler, 0);

    return CheckErrorAndLog("Couldn't assemble the object \"" + this->material->name + "\".");
}

static void updateShaderUniformVariableMVP(GLuint shader, const glm::mat4& mvp) {
    GLint mvpId = glGetUniformLocation(shader, "MVP");
    glProgramUniformMatrix4fv(shader, mvpId, 1, GL_FALSE, glm::value_ptr(mvp));
}

void ObjectRenderable::render(ApplicationPtr app) const {
    if (!this->isInitialized || !this->shader) return;

    glBindVertexArray(app->getVAO(this->type));
    glUseProgram(this->shader);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    updateShaderUniformVariableMVP(this->shader, app->getCamera().translate(this->position, this->orientation));
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
}
