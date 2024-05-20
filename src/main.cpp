#include "app/Application.h"
#include "classes/ObjectRenderable.h"

int main() {
    const std::unordered_map<FileType, File> shaderFiles {
            { FileType::VERTEX_SHADER, File("shaders/ball.vert") },
            { FileType::FRAGMENT_SHADER, File("shaders/ball.frag") }
    };

    Application app { TITLE, WIDTH, HEIGHT };

    app.addObject(new ObjectRenderable(ObjectType::BALL, "./objects/Ball1.obj", shaderFiles));

    return app.run();
}
