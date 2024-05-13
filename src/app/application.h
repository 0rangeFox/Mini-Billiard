//
// Created by João Fernandes on 13/05/2024.
//

#include <iostream>
#include <GLFW/glfw3.h>
#include "../classes/ObjectRenderable.h"

#ifndef MINI_BILLIARD_APPLICATION_H
#define MINI_BILLIARD_APPLICATION_H

class Application {
public:
    Application(const std::string&, int, int);
    ~Application();

    void addObject(const ObjectRenderable*);

    int run();

private:
    int width, height;
    float angle, zoom;
    glm::mat4 mvp;

    GLFWwindow* actualWindow;
    std::vector<const ObjectRenderable*> objects;

    void updateCamera(float, float);
};

#endif //MINI_BILLIARD_APPLICATION_H
