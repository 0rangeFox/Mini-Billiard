#include "app/application.h"

int main() {
    Application app { TITLE, WIDTH, HEIGHT };

    app.addObject(new ObjectRenderable("./objects/Ball1.obj"));

    return app.run();
}
