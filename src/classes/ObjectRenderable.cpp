//
// Created by João Fernandes on 16/05/2024.
//

#include "ObjectRenderable.h"

#include "../macros/GLMacro.hpp"
#include "../utils/ObjectUtil.hpp"
#include "../utils/MaterialUtil.hpp"
#include "../utils/ShaderUtil.hpp"
#include "../utils/TextureUtil.hpp"

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path) : Object(0, 1) {
    std::string _material{};

    this->addResource(FileType::OBJECT, File(path));
    this->type = type;
    this->isInitialized = LoadOBJ(path, _material, this->vertices, this->uvs, this->normals);

    if (!_material.empty()) {
        this->addResource(FileType::MATERIAL, this->getResource<FileType::OBJECT>().copyPathToFile(_material));
        this->material = LoadMaterial(this->getResource<FileType::MATERIAL>().getFullPath());

        if (this->material)
            this->addResource(FileType::IMAGE, this->material->image);
    }
}

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path, const std::unordered_map<FileType, File>& extraFiles) : ObjectRenderable(type, path) {
    this->files.insert(extraFiles.begin(), extraFiles.end());
}

ObjectRenderable::~ObjectRenderable() {
    glDeleteProgram(this->shader);

    delete this->material;
    delete[] this->indices;
    delete[] this->elements;
}

bool ObjectRenderable::generateIndices() {
    this->indices = new GLuint[this->vertices.size()];
    for (int i = 0; i < this->vertices.size(); ++i)
        this->indices[i] = i;
    return true;
}

bool ObjectRenderable::generateElements() {
    this->elements = new GLfloat[this->getTotalElements()];
    GLuint counter = 0;

    for (int i = 0; i < this->vertices.size(); i++) {
        glm::vec3 vVertices = this->vertices[i];
        glm::vec3 vNormals = this->normals[i];
        glm::vec2 vUVs = this->uvs[i];

        // X Y Z
        this->elements[counter++] = vVertices.x;
        this->elements[counter++] = vVertices.y;
        this->elements[counter++] = vVertices.z;

        // NX NY NZ
        this->elements[counter++] = vNormals.x;
        this->elements[counter++] = vNormals.y;
        this->elements[counter++] = vNormals.z;

        // U V
        this->elements[counter++] = vUVs.x;
        this->elements[counter++] = vUVs.y;
    }

    return counter == this->getTotalElements();
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
    this->texture = LoadTexture(this->material->name, this->material->image.getFullPath(), true, app->getTexturesCache());
    this->texture = LoadTexture(this->material->name, this->material->image.getFullPath(), app->getTexturesCache());
    return this->texture > 0;
}

// Unbind the actual VAO and Texture
void unbindTexturesAndVAO() {
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool ObjectRenderable::assemble(ApplicationPtr app) {
    glBindVertexArray(app->getVAO(this->type));

    if (!this->generateIndices() ||
        !this->generateElements() ||
        !this->generateShaders() ||
        !this->generateTextures(app)
    ) {
        unbindTexturesAndVAO();
        return this->isInitialized = false;
    }

    glBindBuffer(GL_ARRAY_BUFFER, app->getVBO(VBO_DATA));
    glBufferStore(GL_ARRAY_BUFFER, this->elements, this->getTotalElements() * sizeof(GLfloat));

    if (this->indices) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app->getVBO(VBO_EBO));
        glBufferStore(GL_ELEMENT_ARRAY_BUFFER, this->indices, this->vertices.size() * sizeof(GLuint))
    }

    GLint verticesId = glGetProgramResLoc(this->shader, "vVertices")
    GLint normalsId = glGetProgramResLoc(this->shader, "vNormals")
    GLint uvsId = glGetProgramResLoc(this->shader, "vUVs")

    GLsizei stride = sizeof(GLfloat) * (3 + 3 + 2);
    glVertexAttribPointer(verticesId, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glVertexAttribPointer(normalsId, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) (3 * sizeof(GLfloat)));
    glVertexAttribPointer(uvsId, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*) (6 * sizeof(GLfloat)));

    glEnableVertexAttribArray(verticesId);
    glEnableVertexAttribArray(normalsId);
    glEnableVertexAttribArray(uvsId);

    GLint locationTexSampler = glGetUniformLocation(this->shader, "textureMapping");
    glProgramUniform1i(this->shader, locationTexSampler, 0);

    unbindTexturesAndVAO();
    return CheckErrorAndLog("Couldn't assemble the object \"" + this->material->name + "\".");
}

static void updateShaderUniformVariableMVP(GLuint shader, const glm::mat4& mvp) {
    GLint mvpId = glGetUniformLocation(shader, "MVP");
    glProgramUniformMatrix4fv(shader, mvpId, 1, GL_FALSE, glm::value_ptr(mvp));
}

void ObjectRenderable::render(ApplicationPtr app) const {
    if (!this->isInitialized || !this->shader) return;

    glBindVertexArray(app->getVAO(this->type));
    glBindTexture(GL_TEXTURE_2D, this->texture);
    updateShaderUniformVariableMVP(this->shader, app->getCamera().getMVP());
    glDrawElements(GL_TRIANGLES, this->vertices.size(), GL_UNSIGNED_INT, nullptr);
}
