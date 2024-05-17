//
// Created by João Fernandes on 17/05/2024.
//

#ifndef MINI_BILLIARD_STRINGUTIL_HPP
#define MINI_BILLIARD_STRINGUTIL_HPP

#include <iostream>
#include <vector>

static std::string GetStringFromVector(const std::vector<std::string>& vString) {
    std::string newString;

    for (const auto& string : vString)
        newString += string;

    return newString;
}

#endif //MINI_BILLIARD_STRINGUTIL_HPP
