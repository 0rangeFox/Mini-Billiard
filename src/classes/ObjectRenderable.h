//
// Created by João Fernandes on 16/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTRENDERABLE_H
#define MINI_BILLIARD_OBJECTRENDERABLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../classes/Material.h"
#include "../classes/Shader.h"
#include "../classes/ObjectType.h"

class Application;
typedef const Application* AppPtr;

class ObjectRenderable {
public:
    explicit ObjectRenderable(const ObjectType&, const std::string&);
    ~ObjectRenderable();

    GLuint getTotalElements() const { return this->vertices.size() * 3 + this->normals.size() * 3 + this->uvs.size() * 2; }

    void assemble(AppPtr);
    void render(AppPtr) const;

private:
    bool isInitialized;
    ObjectType type;
    Material* material = nullptr;
    GLfloat* elements = nullptr;
    GLuint* indices = nullptr;
    GLuint shader = 0;
    std::vector<glm::vec3> vertices{}, normals{};
    std::vector<glm::vec2> uvs{};

    void generateIndices();
    void generateElements();
    void generateShaders(AppPtr);
};

#endif //MINI_BILLIARD_OBJECTRENDERABLE_H
