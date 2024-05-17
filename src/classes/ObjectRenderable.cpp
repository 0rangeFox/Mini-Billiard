//
// Created by João Fernandes on 16/05/2024.
//

#include "ObjectRenderable.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    this->generateTextures();

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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 1);
    updateShaderUniformVariableMVP(this->shader, app->getMVP());

    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}

void ObjectRenderable::generateTextures() {
    GLuint textureName = 0;
    glGenTextures(1, &textureName);


    glBindTexture(GL_TEXTURE_2D, textureName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nChannels;
    unsigned char* imageData = stbi_load(("objects/" + this->material->image).c_str(), &width, &height, &nChannels, 0);
    if (imageData) {
        // Carrega os dados da imagem para o Objeto de Textura vinculado ao target da face
        glTexImage2D(GL_TEXTURE_2D,
            0,					// Nível do Mipmap
            GL_RGB,				// Formato interno do OpenGL
            width, height,		// width, height
            0,					// border
            nChannels == 4 ? GL_RGBA : GL_RGB,	// Formato da imagem
            GL_UNSIGNED_BYTE,	// Tipos dos dados da imagem
            imageData);			// Apontador para os dados da imagem de textura

        // Gera o Mipmap para essa textura
        glGenerateMipmap(GL_TEXTURE_2D);

        // Liberta a imagem da memória do CPU
        stbi_image_free(imageData);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << error << std::endl;
        }
    }
    else {
        std::cout << "Error loading texture!" << std::endl;
    }
}

