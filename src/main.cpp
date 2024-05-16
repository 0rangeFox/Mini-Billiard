#include "app/application.h"

int main() {
    Application app { TITLE, WIDTH, HEIGHT };

    auto test = new ObjectRenderable("./objects/Ball1.obj");
    app.addObject(test);

    return app.run();
}
