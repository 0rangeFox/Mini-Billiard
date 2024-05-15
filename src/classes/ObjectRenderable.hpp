//
// Created by João Fernandes on 13/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTRENDERABLE_HPP
#define MINI_BILLIARD_OBJECTRENDERABLE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../utils/ObjUtil.h"

class ObjectRenderable {
public:
    explicit ObjectRenderable(const std::string& path) {
        LoadOBJ(path);
    }

    explicit ObjectRenderable(std::vector<glm::vec3> obj) {
        this->obj = std::move(obj);
    }

    void render(const glm::mat4& mvp) const {
        auto vertex_stream = (float*) glm::value_ptr(this->obj.front());

        std::vector<glm::vec3> colors{
            glm::vec3(1.0f, 0.0f, 0.0f), // Red
            glm::vec3(1.0f, 1.0f, 0.0f), // Yellow
            glm::vec3(0.0f, 1.0f, 0.0f), // Green
            glm::vec3(0.0f, 1.0f, 1.0f), // Cyan
            glm::vec3(0.0f, 0.0f, 1.0f), // Blue
            glm::vec3(1.0f, 0.0f, 1.0f)  // Magenta
        };

        // Desenha quad em modo imediato
        glBegin(GL_QUADS);
        /* obj.size() * (obj.front().length()) � o mesmo que (6*4)*3 */
        /* 6 faces * 4 v�rtices por face * 3 coordenadas por v�rtice */
        for (int nv = 0; nv < 6 * 4 * 3; nv += 3) {
            // Uma cor por face
            glColor3f(colors[nv / (4 * 3)].r, colors[nv / (4 * 3)].g, colors[nv / (4 * 3)].b);
            glm::vec4 vertex = glm::vec4(vertex_stream[nv], vertex_stream[nv + 1], vertex_stream[nv + 2], 1.0f);
            // C�lculo das coordenadas de recorte
            glm::vec4 transformed_vertex = mvp * vertex;
            // Divis�o de Perspetiva
            glm::vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;
            // Desenho do v�rtice
            glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
        }
        glEnd();
    }

private:
    std::vector<glm::vec3> obj;
};

#endif //MINI_BILLIARD_OBJECTRENDERABLE_HPP
