//
// Created by João Fernandes on 13/05/2024.
//

#ifndef MINI_BILLIARD_APPLICATION_H
#define MINI_BILLIARD_APPLICATION_H

#include <iostream>
#include <GLFW/glfw3.h>
#include "../classes/ObjectRenderable.hpp"

class Application {
public:
    Application(const std::string&, int, int);
    ~Application();

    float getAngle() const { return this->angle; }
    float getZoom() const { return this->zoom; }

    void addObject(const ObjectRenderable*);
    float changeAngle(float);
    float changeZoom(float);

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
