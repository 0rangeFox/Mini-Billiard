#include "ObjectRenderable.h"

#include <glm/gtc/type_ptr.hpp>
#include "../macros/GLMacro.hpp"
#include "../utils/ObjectUtil.hpp"
#include "../utils/MaterialUtil.hpp"
#include "../utils/ShaderUtil.hpp"
#include "../utils/TextureUtil.hpp"
#include <glm/gtc/matrix_inverse.hpp>

ObjectRenderable::ObjectRenderable(const ObjectType& type, const MeshType& mesh) : MeshCollider(mesh, glm::vec3{ 0.f }, glm::vec3{ 0.f }), type(type) {
    this->isInitialized = true;
}

ObjectRenderable::ObjectRenderable(const ObjectType& type, const std::string& path) : MeshCollider(1.f, -10, 10), type(type) {
    std::string materialFileName{};

    this->position.y = 0.f;

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

void ObjectRenderable::refreshModel() {
    glm::mat4 modelTranslated = glm::translate(glm::mat4(1.0f), this->position);

    //                                                                                 Pitch | Yaw | Roll
    modelTranslated = glm::rotate(modelTranslated, glm::radians(this->orientation.x), glm::vec3(1.f, 0.f, 0.f));
    modelTranslated = glm::rotate(modelTranslated, glm::radians(this->orientation.y), glm::vec3(0.f, 1.f, 0.f));
    modelTranslated = glm::rotate(modelTranslated, glm::radians(this->orientation.z), glm::vec3(0.f, 0.f, 1.f));

    this->model = modelTranslated;
}

bool ObjectRenderable::assemble(ApplicationPtr app) {
    this->refreshModel();

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

void ObjectRenderable::updateShaderUniformVariables(ApplicationPtr app) const {
    GLint projectionId = glGetUniformLocation(shader, "Projection");
    glProgramUniformMatrix4fv(shader, projectionId, 1, GL_FALSE, glm::value_ptr(app->getCamera().getProjection()));
    GLint viewId = glGetUniformLocation(shader, "View");
    glProgramUniformMatrix4fv(shader, viewId, 1, GL_FALSE, glm::value_ptr(app->getCamera().getView()));
    GLint modelId = glGetUniformLocation(shader, "Model");
    glProgramUniformMatrix4fv(shader, modelId, 1, GL_FALSE, glm::value_ptr(app->getCamera().getModel()));
    GLint zoomId = glGetUniformLocation(shader, "Zoom");
    glProgramUniformMatrix4fv(shader, zoomId, 1, GL_FALSE, glm::value_ptr(app->getCamera().getZoom()));
    GLint objModelId = glGetUniformLocation(shader, "ObjModel");
    glProgramUniformMatrix4fv(shader, objModelId, 1, GL_FALSE, glm::value_ptr(this->model));

    GLint lightStatusId = glGetUniformLocation(shader, "EnabledLights");
    if (lightStatusId < 0 || !material) return;

    glProgramUniform1iv(shader, glGetUniformLocation(shader, "EnabledLights"), TOTAL_LIGHTS, app->getCamera().getLights());

    glProgramUniform3fv(shader, glGetUniformLocation(shader,"ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));

    // Fonte de luz direcional
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "directionalLight.direction"), 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "directionalLight.ambient"), 1, glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "directionalLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "directionalLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));

    // Fonte de luz pontual #1
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "pointLight[0].position"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 5.0)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "pointLight[0].ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "pointLight[0].diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "pointLight[0].specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
    glProgramUniform1f(shader, glGetUniformLocation(shader, "pointLight[0].constant"), 1.0f);
    glProgramUniform1f(shader, glGetUniformLocation(shader, "pointLight[0].linear"), 0.06f);
    glProgramUniform1f(shader, glGetUniformLocation(shader, "pointLight[0].quadratic"), 0.02f);

    // Fonte de luz pontual #2
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "pointLight[1].position"), 1, glm::value_ptr(glm::vec3(-2.0, 2.0, 5.0)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "pointLight[1].ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "pointLight[1].diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "pointLight[1].specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
    glProgramUniform1f(shader, glGetUniformLocation(shader, "pointLight[1].constant"), 1.0f);
    glProgramUniform1f(shader, glGetUniformLocation(shader, "pointLight[1].linear"), 0.06f);
    glProgramUniform1f(shader, glGetUniformLocation(shader, "pointLight[1].quadratic"), 0.02f);

    glProgramUniform3fv(shader, glGetUniformLocation(shader, "material.emissive"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "material.ambient"), 1, glm::value_ptr(material->ambient_color));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "material.diffuse"), 1, glm::value_ptr(material->diffuse_color));
    glProgramUniform3fv(shader, glGetUniformLocation(shader, "material.specular"), 1, glm::value_ptr(material->specular_color));
    glProgramUniform1f(shader, glGetUniformLocation(shader, "material.shininess"), material->specular_exponent);
}

void ObjectRenderable::render(ApplicationPtr app) const {
    if (!this->isInitialized || !this->shader) return;

    glBindVertexArray(app->getVAO(this->type));
    glUseProgram(this->shader);
    if (this->texture > 0)
        glBindTexture(GL_TEXTURE_2D, this->texture);
    this->updateShaderUniformVariables(app);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
}
