#include "app/Application.h"
#include "classes/ObjectRenderable.h"
#include "models/TableModel.hpp"

int main() {
    const std::unordered_map<FileType, File> shaderFiles {
        { FileType::VERTEX_SHADER, "shaders/ball.vert" },
        { FileType::FRAGMENT_SHADER, "shaders/ball.frag" }
    };

    Application app { TITLE, WIDTH, HEIGHT };
    app.addObject(new TableModel());
    /*for (int i = 1; i <= TOTAL_BALLS; ++i)
        app.addObject(new ObjectRenderable(ObjectType::BALL, "./PoolBalls/Ball" + std::to_string(i) + ".obj", shaderFiles));*/

    return app.run();
}
