#include "app/Application.h"
#include "classes/ObjectRenderable.h"

int main() {
    const std::unordered_map<FileType, File> shaderFiles {
        { FileType::VERTEX_SHADER, File("shaders/ball.vert") },
        { FileType::FRAGMENT_SHADER, File("shaders/ball.frag") }
    };

    Application app { TITLE, WIDTH, HEIGHT };

    for (int i = 1; i <= TOTAL_BALLS; ++i)
        app.addObject(new ObjectRenderable(ObjectType::BALL, "./PoolBalls/Ball" + std::to_string(i) + ".obj", shaderFiles));

    return app.run();
}
