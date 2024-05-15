//
// Created by João Fernandes on 13/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTRENDERABLE_HPP
#define MINI_BILLIARD_OBJECTRENDERABLE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../utils/ObjUtil.h"

class ObjectRenderable {
public:
    explicit ObjectRenderable(const std::string& path) {
       LoadOBJ(path, this->vertices, this->uvs, this->normals);
    }

    void render(const glm::mat4& mvp) const {
       glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    }

private:
    std::vector<glm::vec3> vertices{}, normals{};
    std::vector<glm::vec2> uvs{};
};

#endif //MINI_BILLIARD_OBJECTRENDERABLE_HPP
