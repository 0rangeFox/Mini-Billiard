//
// Created by João Fernandes on 14/05/2024.
//

#ifndef MINI_BILLIARD_ERRORCALLBACK_HPP
#define MINI_BILLIARD_ERRORCALLBACK_HPP

#include <iostream>
#include <GLFW/glfw3.h>

static void ErrorCallback(int error, const char *description) {
    std::cout << "GLFW got an error: " << description << " (Code: " << error << ")" << std::endl;
}

#endif //MINI_BILLIARD_ERRORCALLBACK_HPP
