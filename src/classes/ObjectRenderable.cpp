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

ObjectRenderable::ObjectRenderable(const ObjectType& type) : Object(glm::vec3{ 0.f }, glm::vec3{ 0.f }), type(type) {
    this->position.y = -1;
    this->isInitialized = true;
}

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path) : Object(-10, 10), type(type) {
    std::string materialFileName{};

    this->position.y = 0;

    this->addResource(FileType::OBJECT, File(path));
    this->isInitialized = LoadOBJ(path, materialFileName, this->vertices, this->uvs, this->normals, this->indices, this->elements);

    if (materialFileName.empty())
        return;

    this->addResource(FileType::MATERIAL, this->getResource<FileType::OBJECT>().copyPathToFile(materialFileName));
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
    if (this->material)
        return (this->texture = LoadTexture(this->material->name, this->material->image.getFullPath(), true, app->getTexturesCache())) > 0;
    return true;
}

bool ObjectRenderable::assemble(ApplicationPtr app) {
    glBindVertexArray(app->getVAO(this->type));

    if (!this->generateShaders() || !this->generateTextures(app))
        return this->isInitialized = false;

    glBindBuffer(GL_ARRAY_BUFFER, app->getVBO(this->type, VBO_DATA));
    glBufferData(GL_ARRAY_BUFFER, this->elements.size() * sizeof(GLfloat), this->elements.data(), GL_STATIC_DRAW);

    if (!this->indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app->getVBO(this->type, VBO_EBO));
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);
    }

    GLsizei stride = (3 + 2 + 3) * sizeof(GLfloat);
    GLint verticesId = glGetProgramResLoc(this->shader, "vVertices");
    GLint uvsId = glGetProgramResLoc(this->shader, "vUVs");
    GLint normalsId = glGetProgramResLoc(this->shader, "vNormals");
    GLint texMapId = glGetUniformLocation(this->shader, "textureMapping");

    glVertexAttribPointer(verticesId, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glEnableVertexAttribArray(verticesId);

    if (uvsId >= 0) {
        glVertexAttribPointer(uvsId, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(uvsId);
    }

    if (normalsId >= 0) {
        glVertexAttribPointer(normalsId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) (5 * sizeof(GLfloat)));
        glEnableVertexAttribArray(normalsId);
    }

    if (texMapId >= 0)
        glProgramUniform1i(this->shader, texMapId, 0);

    if (this->material)
        return CheckErrorAndLog("Couldn't assemble the object \"" + this->material->name + "\".");
    return CheckErrorAndLog("Couldn't assemble the object with type " + std::to_string(this->type) + ".");
}

static void updateShaderUniformVariableMVP(GLuint shader, const glm::mat4& mvp) {
    GLint mvpId = glGetUniformLocation(shader, "MVP");
    glProgramUniformMatrix4fv(shader, mvpId, 1, GL_FALSE, glm::value_ptr(mvp));
}

void ObjectRenderable::render(ApplicationPtr app) const {
    if (!this->isInitialized || !this->shader) return;

    glBindVertexArray(app->getVAO(this->type));
    glUseProgram(this->shader);
    if (this->texture > 0)
        glBindTexture(GL_TEXTURE_2D, this->texture);
    updateShaderUniformVariableMVP(this->shader, app->getCamera().translate(this->position, this->orientation));
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
}
