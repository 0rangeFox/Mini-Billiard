//
// Created by João Fernandes on 13/05/2024.
//

#include <iostream>
#include <GLFW/glfw3.h>

#ifndef MINI_BILLIARD_APPLICATION_H
#define MINI_BILLIARD_APPLICATION_H

class Application {
public:
    Application(const std::string&, int, int);
    ~Application();

    int run();

private:
    GLFWwindow* actualWindow;
};

#endif //MINI_BILLIARD_APPLICATION_H
