//
// Created by João Fernandes on 16/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTRENDERABLE_H
#define MINI_BILLIARD_OBJECTRENDERABLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../utils/ObjUtil.h"
#include "../classes/ObjectType.h"

class Application;

class ObjectRenderable {
public:
    explicit ObjectRenderable(const ObjectType&, const std::string&);

    void render(const Application*) const;

private:
    bool isInitialized;
    ObjectType type;
    std::vector<GLuint> indices;
    std::vector<glm::vec3> vertices{}, normals{};
    std::vector<glm::vec2> uvs{};
};

#endif //MINI_BILLIARD_OBJECTRENDERABLE_H
