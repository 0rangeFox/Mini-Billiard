#include "app/application.h"

#define TITLE "Billiard Table"
#define WIDTH 800
#define HEIGHT 600

int main() {
    Application app{ TITLE, WIDTH, HEIGHT };
    return app.run();
}
