//
// Created by João Fernandes on 15/05/2024.
//

#ifndef MINI_BILLIARD_OBJUTIL_HPP
#define MINI_BILLIARD_OBJUTIL_HPP

#include "FileUtil.hpp"

bool LoadOBJ(const std::string& path) {
    ReadFile(path, [](const std::string& line) {
        std::cout << line << std::endl;
    });
}

#endif //MINI_BILLIARD_OBJUTIL_HPP
