#include "app/application.h"

#define TITLE "Billiard Table"
#define WIDTH 800
#define HEIGHT 600

std::vector<glm::vec3> Load3DModel(void) {
    // 6 faces * 4 v�rtices por face
    glm::vec3 point[6 * 4] = {
            // Frente
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(1.0f, -1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            // Tr�s
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(1.0f,  1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f),
            // Direita
            glm::vec3(1.0f, -1.0f,  1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f,  1.0f, -1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            // Esquerda
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            // Cima
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            // Baixo
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f,  1.0f)
    };

    std::vector<glm::vec3> ret;
    for (auto i : point)
        ret.push_back(i);

    return ret;
}

int main() {
    Application app { TITLE, WIDTH, HEIGHT };

    ObjectRenderable testObj { "./objects/Ball1.obj" };
    auto test = new ObjectRenderable(Load3DModel());
    app.addObject(test);

    return app.run();
}
