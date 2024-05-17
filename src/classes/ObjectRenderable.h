//
// Created by João Fernandes on 16/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTRENDERABLE_H
#define MINI_BILLIARD_OBJECTRENDERABLE_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../classes/Material.h"
#include "../classes/ObjectType.h"

class Application;

class ObjectRenderable {
public:
    explicit ObjectRenderable(const ObjectType&, const std::string&);
    ~ObjectRenderable();

    GLuint getTotalElements() const { return this->vertices.size() * 3 + this->normals.size() * 3 + this->uvs.size() * 2; }
    void render(const Application*) const;

private:
    bool isInitialized;
    ObjectType type;
    Material* material = nullptr;
    std::vector<glm::vec3> vertices{}, normals{};
    std::vector<glm::vec2> uvs{};

    GLfloat* generateElements() const;
};

#endif //MINI_BILLIARD_OBJECTRENDERABLE_H
